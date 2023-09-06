#define PIN_ENCODER_A 2 //digital pin
#define PIN_ENCODER_B 3 //digital pin

// pin A filter's Variables
float previous_y_PIN_A = 0, filtered_y_PIN_A = 0;

float current_x_PIN_A = 0, previous_x_PIN_A = 0;


// pin B filter's Variables
float previous_y_PIN_B = 0, filtered_y_PIN_B = 0;

float current_x_PIN_B = 0, previous_x_PIN_B = 0;

void ISR_encoderPIN_A(void)
{
  current_x_PIN_A = digitalRead(PIN_ENCODER_A);

  //filtered_y_PIN_A = -0.256 * previous_y_PIN_A + 0.628 * current_x_PIN_A + 0.628 * previous_x_PIN_A;
}

void ISR_encoderPIN_B(void)
{
  current_x_PIN_B = digitalRead(PIN_ENCODER_B);

  //filtered_y_PIN_B = -0.256 * previous_y_PIN_B + 0.628 * current_x_PIN_B + 0.628 * previous_x_PIN_B;
}



void setup() {

  Serial.begin(9600);
  pinMode(PIN_ENCODER_A, INPUT_PULLUP);
  pinMode(PIN_ENCODER_B, INPUT_PULLUP);

  attachInterrupt(PIN_ENCODER_A, ISR_encoderPIN_A, CHANGE);
  attachInterrupt(PIN_ENCODER_B, ISR_encoderPIN_B, CHANGE);
}

void loop() {
  // update data for Pin A

  filtered_y_PIN_A = -0.256 * previous_y_PIN_A + 0.628 * current_x_PIN_A + 0.628 * previous_x_PIN_A;
  previous_y_PIN_A = filtered_y_PIN_A;
  previous_x_PIN_A = current_x_PIN_A;

  Serial.print("Pin A: ");
  Serial.println(filtered_y_PIN_A);

  // update data for Pin B
  
  filtered_y_PIN_A = -0.256 * previous_y_PIN_A + 0.628 * current_x_PIN_A + 0.628 * previous_x_PIN_A;
  previous_y_PIN_B = filtered_y_PIN_B;
  previous_x_PIN_B = current_x_PIN_B;

  Serial.print("Pin B: ");
  Serial.println(filtered_y_PIN_B);

  delay(50);
}
