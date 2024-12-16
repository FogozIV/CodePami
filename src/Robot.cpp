#include "Robot.h"

Robot::Robot(Motor *left_motor, Motor *right_motor, PRECISION_DATA_TYPE pulse_per_mm, PRECISION_DATA_TYPE track_mm, PRECISION_DATA_TYPE corr_right_wheel,
             PRECISION_DATA_TYPE x, PRECISION_DATA_TYPE y, PRECISION_DATA_TYPE a) : pos(x, y, a), pulse_per_mm(pulse_per_mm), track_mm(track_mm),
                                             corr_right_wheel(corr_right_wheel), total_distance(0.0f), target_distance(0.0f), total_angle(0.0f), target_angle(0.0f) {
    this->left_motor = left_motor;
    this->right_motor = right_motor;
    this->targets = static_cast<Target **>(malloc(sizeof(Target *) * this->max_targets));
}

void Robot::computePosition(int16_t delta_left_tick, int16_t delta_right_tick) {
    PRECISION_DATA_TYPE mult = 1;
    PRECISION_DATA_TYPE angle = correctAngle(target_angle - total_angle);
    //We go backward
    if(!done_distance && (angle < -90 || angle > 90))
        mult = -1;
    PRECISION_DATA_TYPE distance = ((PRECISION_DATA_TYPE) (delta_left_tick + delta_right_tick * corr_right_wheel)) / (2.0f * pulse_per_mm);
    total_distance += mult* distance;
    PRECISION_DATA_TYPE dtheta = (delta_right_tick * corr_right_wheel - delta_left_tick) / (2.0f * pulse_per_mm);
    PRECISION_DATA_TYPE arc_angle = 2 * dtheta / track_mm;
    PRECISION_DATA_TYPE deg_arc_angle = arc_angle/M_PI * 180.0f;
    total_angle += deg_arc_angle;
    PRECISION_DATA_TYPE dx;
    PRECISION_DATA_TYPE dy;
    if (dtheta == 0) {
        dx = cos(this->pos.getAngleRad()) * distance;
        dy = sin(this->pos.getAngleRad()) * distance;
    } else {
        PRECISION_DATA_TYPE r = distance * track_mm / (dtheta * 2.0f);
        dx = r * (-sin(this->pos.getAngleRad()) + sin(this->pos.getAngleRad() + arc_angle));
        dy = r * (cos(this->pos.getAngleRad()) - cos(this->pos.getAngleRad() + arc_angle));
    }
    this->pos += Position(dx, dy, arc_angle);
}

void Robot::control() {
    if(pid_distance != nullptr && pid_angle != nullptr){
        PRECISION_DATA_TYPE angle = correctAngle(target_angle - total_angle);
        PRECISION_DATA_TYPE mult = 1;
        if((angle < -90 || angle > 90) && !done_distance)
            mult = -1;
        PRECISION_DATA_TYPE distance_term = mult*((done_distance && abs(target_distance - total_distance) < 5) ? 0 : pid_distance->evaluate(target_distance - total_distance));
        PRECISION_DATA_TYPE angle_term = done_angle ? 0 : mult!=1 ?pid_angle->evaluate(correctAngle(target_angle - total_angle-180)) :pid_angle->evaluate(correctAngle(target_angle - total_angle));
        int16_t left_wheel = constrain(constrain(distance_term, -200, 200) - constrain(angle_term, -200, 200), -255, 255);
        int16_t right_wheel = constrain(constrain(distance_term, -200, 200) + constrain(angle_term, -200, 200), -255, 255);
        this->right_motor->setPWM(right_wheel);
        this->left_motor->setPWM(left_wheel);
    }
}

Position Robot::getPosition() const {
    return pos;
}

Robot::~Robot() {
    delete pid_distance;
    delete pid_angle;
    delete left_motor;
    delete right_motor;
    for(uint16_t i = 0; i < target_count; i++)
        delete targets[i];
    free(targets);
}

void Robot::setPidDistance(PID *pidDistance) {
    delete pid_distance;
    pid_distance = pidDistance;
}

void Robot::setPidAngle(PID *pidAngle) {
    delete pid_angle;
    pid_angle = pidAngle;
}


size_t Robot::printTo(Print &p) const {
    size_t data = 0;
#ifdef DEBUG_TXT
    data = p.print("Position : ");
    data += p.print(pos);
    data += p.print(", target distance : ");
    data += p.print(target_distance);
    data += p.print(", total distance : ");
    data += p.print(total_distance);
    data += p.print(", target angle : ");
    data += p.print(target_angle);
    data += p.print(", total angle : ");
    data += p.print(total_angle);
#endif
    return data;
}

void Robot:: computeTarget() {
    if(this->target_count <= this->target_index)
        return;
    Target* target = this->targets[this->target_index];
    target->call_init();
    target->process();
    if(target->is_done()){
        target->on_done();
        this->target_index++;
    }
}

bool Robot::addTarget(Target *target) {
    if(this->target_count >= this->max_targets){
        auto** pTarget = static_cast<Target **>(realloc(this->targets, sizeof(Target *) * (this->max_targets + 2)));
        if(pTarget == nullptr){
            return false;
        }
        this->targets = pTarget;
        this->max_targets+=2;
    }
    this->targets[this->target_count] = target;
    this->target_count++;
    return true;
}

PRECISION_DATA_TYPE Robot::getTargetDistance() const {
    return target_distance;
}

PRECISION_DATA_TYPE Robot::getTargetAngle() const {
    return target_angle;
}

bool Robot::isDoneDistance() const {
    return done_distance;
}

bool Robot::isDoneAngle() const {
    return done_angle;
}

void Robot::setTargetDistance(PRECISION_DATA_TYPE targetDistance) {
    target_distance = targetDistance;
}

void Robot::setTargetAngle(PRECISION_DATA_TYPE targetAngle) {
    target_angle = targetAngle;
}

void Robot::setDoneDistance(bool doneDistance) {
    done_distance = doneDistance;
}

void Robot::setDoneAngle(bool doneAngle) {
    done_angle = doneAngle;
}

PRECISION_DATA_TYPE Robot::getRampSpeed() const {
    return ramp_speed;
}

void Robot::setRampSpeed(PRECISION_DATA_TYPE rampSpeed) {
    ramp_speed = rampSpeed;
}

PRECISION_DATA_TYPE Robot::getTotalDistance() const {
    return total_distance;
}

PRECISION_DATA_TYPE Robot::getTotalAngle() const {
    return total_angle;
}

PRECISION_DATA_TYPE Robot::getRampSpeedAngle() const {
    return ramp_speed_angle;
}

void Robot::setRampSpeedAngle(PRECISION_DATA_TYPE rampSpeedAngle) {
    ramp_speed_angle = rampSpeedAngle;
}

PRECISION_DATA_TYPE Robot::getRelativeAngle(PRECISION_DATA_TYPE a) const {
    return getTotalAngle() + a;
}

PRECISION_DATA_TYPE Robot::getAbsoluteAngle(PRECISION_DATA_TYPE a) const {
    return getTotalAngle() + a - correctAngle(getTotalAngle());
}

void Robot::setTotalDistance(PRECISION_DATA_TYPE totalDistance) {
    total_distance = totalDistance;
}

void Robot::setTotalAngle(PRECISION_DATA_TYPE totalAngle) {
    total_angle = totalAngle;
}

Motor::Motor(uint8_t dir_pin, uint8_t pwm_pin, bool inverse) {
    this->dir_pin = dir_pin;
    this->pwm_pin = pwm_pin;
    pinMode(dir_pin, OUTPUT);
    pinMode(pwm_pin, OUTPUT);
    analogWrite(pwm_pin, 0);
    this->inverse = inverse;
}

void Motor::setPWM(int16_t pwm) {
    pwm *= inverse ? -1 : 1;
    digitalWrite(dir_pin, pwm < 0 ? HIGH : LOW);
    analogWrite(pwm_pin, abs(pwm));
}

PRECISION_DATA_TYPE correctAngle(PRECISION_DATA_TYPE angle) {
    return fmod(fmod(angle + 180, 360) - 360, 360) + 180;
}
