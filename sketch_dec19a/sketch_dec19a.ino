#include <SoftwareSerial.h>

byte TX_PIN = D1 , RX_PIN = D2;


SoftwareSerial Soft_Serial(RX_PIN, TX_PIN);  // Khởi tạo đối tượng SoftwareSerial


void setup() {
  Serial.begin(9600);    // Khởi động Serial Monitor với tốc độ 9600
  Soft_Serial.begin(9600); // Khởi động giao tiếp với cổng TTL cũng với tốc độ 9600
  Serial.println("Welcome");
}

void loop() {
  
  if (Soft_Serial.available()) { // Kiểm tra xem có dữ liệu nào từ cổng TTL không
    String receivedString = ""; // Tạo một chuỗi để lưu dữ liệu nhận được
    Serial.println("Có dữ liệu");
    receivedString = Soft_Serial.readString();
    Serial.println(receivedString);

  }
  // Các hoạt động khác có thể thêm ở đây
}
