const int COLUMN_DATA_PIN = 2;
const int COLUMN_CLK_PIN = 3;
const int COLUMN_REG_PIN = 4;

const int ROW_DATA_PIN = 5;
const int ROW_CLK_PIN = 6;
const int ROW_REG_PIN = 7;

const int EN_PIN = 8;

const int BRIGHTNESS_LEVEL = 16;
const int BRIGHTNESS_GAP = 256 / BRIGHTNESS_LEVEL;
const int ROW_DURATION = 200;

uint8_t *matrix;
uint8_t *buffer;

size_t size = 0;

void setup() {
  pinMode(COLUMN_DATA_PIN, OUTPUT);
  pinMode(COLUMN_CLK_PIN, OUTPUT);
  pinMode(COLUMN_REG_PIN, OUTPUT);
  pinMode(ROW_DATA_PIN, OUTPUT);
  pinMode(ROW_CLK_PIN, OUTPUT);
  pinMode(ROW_REG_PIN, OUTPUT);
  
  pinMode(EN_PIN, OUTPUT);

  digitalWrite(EN_PIN, HIGH);

  digitalWrite(COLUMN_CLK_PIN, LOW);
  digitalWrite(COLUMN_REG_PIN, LOW);
  digitalWrite(ROW_CLK_PIN, LOW);
  digitalWrite(ROW_REG_PIN, LOW);

  matrix = malloc(8 * 8);
  buffer = malloc(8 * 8);

  for (int i = 0; i < 8 * 8; i++) {
    matrix[i] = i * 4;
  }

  Serial.begin(250000);

  while (Serial.available()) {
    Serial.read();
  }
}

void loop() {
  for (int i = 0; i < 8; i++) {
    readSerial();
    
    // set the row first
    digitalWrite(ROW_DATA_PIN, i == 0 ? LOW : HIGH);
    digitalWrite(ROW_CLK_PIN, HIGH);
    digitalWrite(ROW_CLK_PIN, LOW);
    digitalWrite(ROW_REG_PIN, HIGH);
    digitalWrite(ROW_REG_PIN, LOW);

    // set column repeatedly based on brightness level
    for (int l = 0; l < 256; l += BRIGHTNESS_GAP) {
      int indexOffset = i * 8;
      for (int j = 0; j < 8; j++) {
        digitalWrite(COLUMN_DATA_PIN, matrix[indexOffset + 7 - j] > l ? HIGH : LOW);
        digitalWrite(COLUMN_CLK_PIN, HIGH);
        digitalWrite(COLUMN_CLK_PIN, LOW);
      }
      digitalWrite(COLUMN_REG_PIN, HIGH);
      digitalWrite(COLUMN_REG_PIN, LOW);

      digitalWrite(EN_PIN, LOW);
      delayMicroseconds(ROW_DURATION / BRIGHTNESS_LEVEL);
    }

    digitalWrite(EN_PIN, HIGH);
  }
}
void readSerial() {
  int available = Serial.available();
  if (available <= 0) return;

  int remaining = 8 * 8 - size;

  if (available > remaining) {
    Serial.readBytes(&buffer[size], remaining);
    uint8_t *tmp = buffer;
    buffer = matrix;
    matrix = tmp;
    
    Serial.readBytes(buffer, available - remaining);
    size = available - remaining;
  } else {
    Serial.readBytes(&buffer[size], available);
    size += available;
  }
}
