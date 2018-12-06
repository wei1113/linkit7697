int t;
int h;

char _lwifi_ssid[] = "Wei";
char _lwifi_pass[] = "1234567890";

MCSDevice mcs("DCJMF2B9", "ajkFrS8rdrmEVZic");
MCSDisplayInteger temp("temp");
MCSDisplayInteger humid("humid");

DHT __dht2(4, DHT11);

void setup()
{
  Serial.begin(9600);

  mcs.addChannel(temp);
  mcs.addChannel(humid);
  Serial.println("Wi-Fi");
  while (WiFi.begin(_lwifi_ssid, _lwifi_pass) != WL_CONNECTED) { delay(1000); }
  Serial.println("Wi-Fi");
  while(!mcs.connected()) { mcs.connect(); }
  Serial.println("MCS");
  Serial.begin(9600);
  __dht2.begin();
}

void loop()
{
  while (!mcs.connected()) {
    mcs.connect();
    if (mcs.connected()) { Serial.println("MCS 已重新連線"); }
  }
  mcs.process(100);

  t = __dht2.readTemperature();
  h = __dht2.readHumidity();
  temp.set(t);
  humid.set(h);

  Serial.print("攝氏溫度 : ");
  Serial.println(t);
  Serial.print("相對溼度 :");
  Serial.println(h);

  delay(1000);
}
