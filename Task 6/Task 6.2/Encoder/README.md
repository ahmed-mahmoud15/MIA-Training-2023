# Software Practical Low Pass Filter (LPF)

## Pin Definitions

Define 2 variables to hold the pins numbers

```Arduino
#define PIN_ENCODER_A 2
#define PIN_ENCODER_B 3
```
## Filter Variables
Next, the code declares variables for pin A and pin B filtering:

```
// pin A filter's Variables
float previous_y_PIN_A = 0, filtered_y_PIN_A = 0;
float current_x_PIN_A = 0, previous_x_PIN_A = 0;

// pin B filter's Variables
float previous_y_PIN_B = 0, filtered_y_PIN_B = 0;
float current_x_PIN_B = 0, previous_x_PIN_B = 0;
```
## Derive the Equation

Using python [notebook](https://colab.research.google.com/drive/1DhEJ4ISUISa7pP77onCkMx4U8dfOcuvE#scrollTo=1eeedea4) provided in the sessions

- `Pulse_per_rotation` holds the number of pulses per one rotation
- `wheel_radius` holds the radius of motorized wheel in cm
- `max_speed` holds the maximum speed in m/s
- `omega` is the angular velocity in rad/s
- `rotation_per_sec` is the angular velocity also but in rotation per second
- `Pulse_per_sec` The maximum number of pulses per second aka Frequency for all pins
- `Pulse_per_sec_one_pin` the number of Palses in one pin

```python
Pulse_per_rotation = 540                                         # PPR
wheel_radius       = 0.2                                         # meter
max_speed          = 0.5                                         # m/s

omega = max_speed / wheel_radius                                 # Rad/s

rotation_per_sec   =  omega / (2 * np.pi)                        # RPS
Pulse_per_sec      = Pulse_per_rotation *   rotation_per_sec     # PPS

Pulse_per_sec_one_pin = Pulse_per_sec / 2
```

Then setting the Cutoff Frequency to a value greater than number of pulses in one pin

```python
cutoff_Freq   = Pulse_per_sec_one_pin * 5
```

This give the Equation of the filter

`filtered_y = -0.256 * previous_y + 0.628 * current_x + 0.628 * previous_x`

## Interrupt Service Routines (ISRs)

The code defines two interrupt service routines (ISRs) that handle the changes on the encoder pins:

```
void ISR_encoderPIN_A(void)
{
  current_x_PIN_A = digitalRead(PIN_ENCODER_A);
  filtered_y_PIN_A = -0.256 * previous_y_PIN_A + 0.628 * current_x_PIN_A + 0.628 * previous_x_PIN_A;
}

void ISR_encoderPIN_B(void)
{
  current_x_PIN_B = digitalRead(PIN_ENCODER_B);
  filtered_y_PIN_B = -0.256 * previous_y_PIN_B + 0.628 * current_x_PIN_B + 0.628 * previous_x_PIN_B;
}
```

Each ISR reads the current state of the corresponding encoder pin and calculates the filtered value using the equation.

## Setup Function

- Initiates the serial communication at a baud rate of 9600 using `Serial.begin(9600)`.
- Sets the pin modes of `PIN_ENCODER_A` and `PIN_ENCODER_B` to `INPUT_PULLUP` using `pinMode()`. This enables the internal pull-up resistors for these pins.
- Attaches the ISRs to the corresponding pins using the `attachInterrupt()` function and the `digitalPinToInterrupt()` macro. This ensures that the ISRs are called when a change is detected on the specified pins.

## Loop Function

- Updates the variables for pin A filtering by assigning the previous values and current values to the respective variables.
- Prints the filtered value of pin A using `Serial.print()` and `Serial.println()`.
- Do the thing with pin B.
- Introduces a delay of 50 milliseconds using `delay()` before repeating the loop.
