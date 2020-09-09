/* 
 * piano stairs
 */
#define nSensors_A 2
#define nSensors_B 2
#define nSensors_micomA 4
#define THRSLD 80

TaskHandle_t th[2];
portTickType Delay = 10 / portTICK_RATE_MS;

// define pin numbers of echo/trig pins
int echoPin_A[nSensors_A] = {16, 15}; // 4, 5
int trigPin_A[nSensors_A] = {5, 0};
int echoPin_B[nSensors_B] = {13, 26}; // 6, 7
int trigPin_B[nSensors_B] = {12, 33};
//int echoPin_A[nSensors_A] = {2, 5, 13, 21, 23};
//int trigPin_A[nSensors_A] = {0, 17, 12, 18, 22};
//int echoPin_B[nSensors_B] = {15, 20, 19, 22};
//int trigPin_B[nSensors_B] = {19, 21, 18, 23};

// status
int status_A[nSensors_A] = {0};
int status_B[nSensors_B] = {0};
// status2
int status_A2[nSensors_A] = {0};
int status_B2[nSensors_B] = {0};

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
      if (drt_A > 0){
        dst_A = drt_A * 340.0 / 1000000;
        dst_A = dst_A * 100.0;
      }

      if(dst_A < THRSLD){
        if(status_A[i] == 0){
//          Serial.print(i);
//          Serial.print(", ");
//          Serial.println(dst_A);
          Serial.write(i+nSensors_micomA);
          status_A[i] = 1;
        }
      }else{
         status_A[i] = 0;
      }

//      Serial.print("A");
//      Serial.print(i);
//      Serial.print(" : ");
//      Serial.println(dst_A);

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
      if (drt_B > 0){
        dst_B = drt_B * 340.0 / 1000000;
        dst_B = dst_B * 100.0;
      }
 
      if(dst_B < THRSLD){
        if(status_B[i] == 0){
//          Serial.print(i + nSensors_A);
//          Serial.print(", ");
//          Serial.println(dst_B);
          Serial.write(i + nSensors_A+ nSensors_micomA );
          status_B[i] = 1;
        }
      }else{
         status_B[i] = 0;
      }

//      Serial.print("B");
//      Serial.print(i);
//      Serial.print(" : ");
//      Serial.println(dst_B);

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
