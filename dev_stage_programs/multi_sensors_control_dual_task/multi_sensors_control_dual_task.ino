/* 
 * piano stairs
 */
#define nSensors_A 5
#define nSensors_B 5
#define THRSLD 100

TaskHandle_t th[2];
portTickType Delay = 3 / portTICK_RATE_MS;

// define pin numbers of echo/trig pins
int echoPin_A[nSensors_A] = {35, 32, 25, 27, 12};
int trigPin_A[nSensors_A] = {21, 33, 26, 14, 13};
int echoPin_B[nSensors_B] = {23, 18, 17, 4, 2};
int trigPin_B[nSensors_B] = {22, 5, 16, 0, 15};

// status
int status_A[nSensors_A] = {0};
int status_B[nSensors_B] = {0};

int drt_A, drt_B; // duration
float dst_A, dst_B; // distance

void TaskA(void *pvParameters){
  while(1){
    for(int i=0; i < nSensors_A; i++){
      // trigger
      digitalWrite(trigPin_A[i], LOW);
      ets_delay_us(1);
      digitalWrite(trigPin_A[i], HIGH);
      ets_delay_us(11);
      digitalWrite(trigPin_A[i], LOW);

      // echo
      int drt_A = pulseIn(echoPin_A[i], HIGH) / 2;

      // convert time to distance
      dst_A = (float)drt_A * 340.0 / 1000.0 / 1000.0;
      dst_A = dst_A * 100.0;

      if(dst_A < THRSLD){
        if(status_A[i] == 0){
          Serial.write(i);
          status_A[i] = 1;
        }
      }else{
         status_A[i] = 0;
      }

      Serial.print("A");
      Serial.print(i);
      Serial.print(" : ");
      Serial.println(dst_A);

      vTaskDelay(Delay);
      }
    }
  }

void TaskB(void *pvParameters){
  while(1){
    for(int i=0; i < nSensors_B; i++){
      // trigger
      digitalWrite(trigPin_B[i], LOW);
      ets_delay_us(1);
      digitalWrite(trigPin_B[i], HIGH);
      ets_delay_us(11);
      digitalWrite(trigPin_B[i], LOW);

      // echo
      int drt_B = pulseIn(echoPin_B[i], HIGH) / 2;

      // convert time to distance
      dst_B = (float)drt_B * 340.0 / 1000.0 / 1000.0;
      dst_B = dst_B * 100.0;

      if(dst_B < THRSLD){
        if(status_B[i] == 0){
          Serial.write(i + nSensors_B);
          status_B[i] = 1;
        }
      }else{
         status_B[i] = 0;
      }

      Serial.print("B");
      Serial.print(i);
      Serial.print(" : ");
      Serial.println(dst_B);

      vTaskDelay(Delay);
      }
    }
  }
  
void setup() {
  Serial.begin(9600);

  // define pin mode
  for (int i=0; i < nSensors_A; i++){
    pinMode(trigPin_A[i], OUTPUT);
    pinMode(echoPin_A[i], INPUT);
    }
  for (int i=0; i < nSensors_B; i++){
    pinMode(trigPin_B[i], OUTPUT);
    pinMode(echoPin_B[i], INPUT);
    }
  
  xTaskCreatePinnedToCore(TaskA, "TaskA", 4096, NULL, 1, &th[0], 0);
  xTaskCreatePinnedToCore(TaskB, "TaskB", 4096, NULL, 2, &th[1], 1);
}

void loop() {
  // put your main code here, to run repeatedly:

}
