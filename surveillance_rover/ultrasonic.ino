
void ultrasonic_left()
{
  //  Serial.print(" Ultrasonic Left ");
  // Clears the trigPin_left condition
  digitalWrite(trigPin_left, LOW);
  delayMicroseconds(2);
  // Sets the trigPin_left HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin_left, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_left, LOW);
  // Reads the echoPin_left, returns the sound wave travel time in microseconds
  duration_left = pulseIn(echoPin_left, HIGH);
  // Calculating the distance
  distance_left = duration_left * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
}

void ultrasonic_right()
{
  //  Serial.print(" Ultrasonic Right");
  // Clears the trigPin_left condition
  digitalWrite(trigPin_right, LOW);
  delayMicroseconds(2);
  // Sets the trigPin_left HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin_right, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_right, LOW);
  // Reads the echoPin_left, returns the sound wave travel time in microseconds
  duration_right = pulseIn(echoPin_right, HIGH);
  // Calculating the distance
  distance_right = duration_right * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
}


void checkObstacles()
{
  if (motion == true) {
    if(distance_left <= 25 && distance_left >= 0 || distance_right <= 25  && distance_right >= 0 && abs(distance_left - distance_right) <= 5)
  {
    digitalWrite(BUZZ, HIGH); b = 2; Serial.println("      Reverse  ");
    backward(b);
    delay(500); f = 2;
    forward(f);
  }
  else if ( motion == true && distance_left <= 40 && distance_left > 25 && distance_right <= 40 && distance_right > 25 && abs(distance_left - distance_right) <= 5)
  {
    digitalWrite(BUZZ, HIGH); l = 3; Serial.println("      Right maar bhaiii");
    left(l);
    delay(500);
    forward(f);
    if (autonomous == false) count_lboth++;
  }
  else if (motion == true && distance_left <= 40 && distance_left > 25 &&  abs(distance_left - distance_right) >= 5)
  {
    digitalWrite(BUZZ, HIGH); l = 2; Serial.println("   gaya   left ");
    left(l);
    delay(500);
    forward(f);
    if (autonomous == false) count_l++;
  }
  else if (motion == true && distance_right <= 40 && distance_right > 25 && abs(distance_left - distance_right) >= 5)
  {
    digitalWrite(BUZZ, HIGH); r = 2; Serial.println("      Right gaya");
    right(r);
    delay(500);
    forward(f);
    if (autonomous == false) count_r++;
  }
  }
  
  //  else if (distance_left<=25 && distance_left>=0 && motion == true && abs(distance_left-distance_right) >= 5)
  //  {
  //      digitalWrite(BUZZ, HIGH);bl=2; Serial.println("      Back left");
  //    backward_left(bl);
  //    delay(500); f=2;
  //    forward(f);
  //  }
  //  else if (distance_right <= 25 && distance_right>=0 && motion == true && abs(distance_left-distance_right) >= 5)
  //  {
  //      digitalWrite(BUZZ, HIGH); //Stop(); //delay(500);
  //       br=2;Serial.println("Back right");
  //    backward_right(br);
  //    delay(500); f=2;
  //    forward(f);
  //  }
  
  digitalWrite(BUZZ, LOW);
  if (autonomous == false && motion == true)
  {
    if (count_lboth > 0 && distance_right > 40 && distance_left > 40)
    {
      r = 3;
      right(r); delay(500);
      count_lboth--;
    }
    if (count_l > 0 && distance_right > 40 && distance_left > 40)
    {
      r = 2;
      right(r); delay(500);
      count_l--;
    }
    if (count_r > 0 && distance_right > 40 && distance_left > 40)
    {
      l = 2;
      left(l); delay(500);
      count_r--;
    }
    f = 2;
    forward(f);
  }
}
