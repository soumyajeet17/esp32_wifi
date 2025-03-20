#include <Arduino.h>
#include "WiFi.h"
#include <ros.h>
#include <std_msgs/Float32.h>

// Wi-Fi Credentials
const char* ssid = "soumyajeet17";
const char* password = "Apache@1600";

IPAddress ip(192, 168, 46, 47);
IPAddress server(10, 42, 0, 1);
uint16_t serverPort = 11412;

// Data Variables
float my_data = 1.0;       // ESP32's own data
float received_data = 0.0; // Data received from another ESP32

ros::NodeHandle nh;

// Publisher & Subscriber
std_msgs::Float32 msg;
ros::Publisher pub("n1", &msg);

// Callback function for subscriber
void dataCallback(const std_msgs::Float32 &msg)
{
  received_data = msg.data;
  my_data = my_data + 0.1 * (msg.data - my_data);
}
ros::Subscriber<std_msgs::Float32> sub("n2", &dataCallback);

void setupWiFi()
{
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  { 
    delay(500);
    Serial.print("."); 
  }
  Serial.println("\nConnected to Wi-Fi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void setup()
{
  Serial.begin(115200);
  setupWiFi();

  nh.getHardware()->setConnection(server, serverPort);
  nh.initNode();

  // Register Publisher & Subscriber
  nh.advertise(pub);
  nh.subscribe(sub);
}

void loop()
{
  if (nh.connected())
  {
    Serial.println("Connected to ROS");

    // Publish my_data
    msg.data = my_data;
    pub.publish(&msg);
  }
  else
  {
    Serial.println("Not Connected to ROS");
  }

  nh.spinOnce();
  delay(1000);
}M
