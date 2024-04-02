void confSelector(){
    pinMode(RCSelector, INPUT);
};
unsigned char workingMode(){
    return digitalRead(RCSelector);
};