void current_location()
{
  // Read initial location and calculate distance and direction to destination
  double latitude = gps.location.lat();
  double longitude = gps.location.lng();
  double distance = TinyGPSPlus::distanceBetween(latitude, longitude, destLat, destLng);
  double bearing = TinyGPSPlus::courseTo(latitude, longitude, destLat, destLng);
  int direction = bearing - compass_heading();

  Number_of_SATS = (int)(gps.satellites.value());
  Serial.print(Number_of_SATS);
  Serial.print(" SATs ");
  Serial.print("Initial latitude: ");
  Serial.println(latitude, 6);
  Serial.print("Initial longitude: ");
  Serial.println(longitude, 6);
  Serial.print("Destination latitude: ");
  Serial.println(destLat, 6);
  Serial.print("Destination longitude: ");
  Serial.println(destLng, 6);
  Serial.print("Initial distance: ");
  Serial.print(distance);
  Serial.println(" meters");
  Serial.print("Initial direction: ");
  Serial.print(direction);
  Serial.println(" degrees");
}

void autonomous_rover()
{
  //gps
//  Serial.println("Searching for Satellites ");
//  while (Number_of_SATS <= 4)                         // Wait until x number of satellites are acquired before starting main loop
//  {
//    while (gpsSerial.available() > 0) {
//      gps.encode(gpsSerial.read());
//    }
//    Number_of_SATS = (int)(gps.satellites.value());   // Query Tiny GPS for the number of Satellites Acquired
//  }
  Serial.print(Number_of_SATS);
  Serial.println("    Satellites Acquired");
  
  autonomous = true;
  current_location();
  while (abs(distance) > 10) { // Move towards destination while distance is greater than 1 meter
    if (direction >= 315 || direction <= 45) forward(2);
    else if (direction > 45 && direction <= 135) only_right(2);
    else if (direction > 135 && direction <= 225) backward(2);
    else if (direction > 225 && direction <= 315) only_left(2);

    // Wait for a short period of time before taking another GPS reading and updating movement
    delay(100);

    // Update current location
    while (gpsSerial.available() > 0) {
      if (gps.encode(gpsSerial.read())) {
        double newLatitude = gps.location.lat();
        double newLongitude = gps.location.lng();

        // Check for obstacles
        checkObstacles();

        // Calculate new distance and direction to destination
        distance = TinyGPSPlus::distanceBetween(newLatitude, newLongitude, destLat, destLng);
        bearing = TinyGPSPlus::courseTo(newLatitude, newLongitude, destLat, destLng);

        // Update direction to move in based on compass reading or manual direction
        direction = bearing - compass_heading();
        
        if (direction >= 315 || direction <= 45) forward(2);
        else if (direction > 45 && direction <= 135) only_right(2);
        else if (direction > 135 && direction <= 225) backward(2);
        else if (direction > 225 && direction <= 315) only_left(2);
    
        // Wait for a short period of time before taking another GPS reading and updating movement
        delay(100);
        
        Serial.print("New latitude: ");
        Serial.println(newLatitude, 6);
        Serial.print("New longitude: ");
        Serial.println(newLongitude, 6);
        Serial.print("Distance remaining: ");
        Serial.print(distance);
        Serial.println(" meters");
        Serial.print("Direction to move in: ");
        Serial.print(direction);
        Serial.println(" degrees");
      }

      // Stop the robot once it has reached the destination
      if (abs(distance) <= 10)
      {
        Stop();
        Serial.println("Destination reached!");
        autonomous = false;
        delay(5000); // Wait for 5 seconds before restarting loop
      }
    }
  }
}
