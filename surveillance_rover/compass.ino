//float compass_heading()
//{
//  int norm = compass.readNormalize();
//  // Calculate heading
//  float heading = atan2(norm.YAxis, norm.XAxis);
//  // Set declination angle on your location and fix heading
//  // You can find your declination on: http://magnetic-declination.com/
//  // (+) Positive or (-) for negative
//  // For Bytom / Poland declination angle is 4'26E (positive)
//  // Formula: (deg + (min / 60.0)) / (180 / M_PI);
//  float declinationAngle = (0.0 - (4.0 / 60.0)) / (180 / PI);
//  heading += declinationAngle;
//  // Correct for heading < 0deg and heading > 360deg
//  if (heading < 0) {
//    heading += 2 * PI;
//  }
//  if (heading > 2 * PI) {
//    heading -= 2 * PI;
//  }
//  // Convert to degrees
//  float headingDegrees = heading * 180 / M_PI;
//  // Output
//  Serial.print(" Heading = ");
//  Serial.print(heading);
//  Serial.print(" Degress = ");
//  Serial.print(headingDegrees);
//  Serial.println();
//  delay(100);
//  return headingDegrees;
//}
