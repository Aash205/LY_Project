int temp5 = 0;
void dtmf()
{
  Serial.print(" DTMF ");
  int temp1 = digitalRead(D0);
  int temp2 = digitalRead(D1);
  int temp3 = digitalRead(D2);
  int temp4 = digitalRead(D3);
  int temp5 = digitalRead(D4);

//  if(temp1 >=1) temp1=1;
//  if(temp2 >=1) temp2=1;
  if (temp1 == 1 && temp2 == 0 && temp3 == 0 && temp4 == 0 && temp5 == 1) //1
  {
    dtmf_no = 1;
  }
  else if (temp1 == 0 && temp2 == 1 && temp3 == 0 && temp4 == 0 && temp5 == 1) //2
  {
    dtmf_no = 2;
  }
  else if (temp1 == 1 && temp2 == 1 && temp3 == 0 && temp4 == 0 && temp5 == 1) //3
  {
    dtmf_no = 3;
  }
  else if (temp1 == 0 && temp2 == 0 && temp3 == 1 && temp4 == 0 && temp5 == 1) //4
  {
    dtmf_no = 4;
  }

  else if (temp1 == 1 && temp2 == 0 && temp3 == 1 && temp4 == 0 && temp5 == 1) //5
  {
    dtmf_no = 5;
  }
  else if (temp1 == 0 && temp2 == 1 && temp3 == 1 && temp4 == 0 && temp5 == 1) //6
  {
    dtmf_no = 6;
  }

  else if (temp1 == 1 && temp2 == 1 && temp3 == 1 && temp4 == 0 && temp5 == 1) //7
  {
    dtmf_no = 7;
  }
  else if (temp1 == 0 && temp2 == 0 && temp3 == 0 && temp4 == 1 && temp5 == 1) //8
  {
    dtmf_no = 8;
  }

  else if (temp1 == 1 && temp2 == 0 && temp3 == 0 && temp4 == 1 && temp5 == 1) //9
  {
    dtmf_no = 9;
  }

  else if (temp1 == 0 && temp2 == 0 && temp3 == 1 && temp4 == 1 && temp5 == 1) //#
  {
    dtmf_no = 555;
  }

  else if (temp1 == 1 && temp2 == 1 && temp3 == 0 && temp4 == 1 && temp5 == 1) //*
  {
    dtmf_no = 999;
  }
  else if (temp1 == 0 && temp2 == 1 && temp3 == 0 && temp4 == 1 && temp5 == 1) //0
  {
    dtmf_no = 0;
  }
  if (temp5 == 1)
  {
    delay(300);
    Serial.println("---------");
    temp5 = 0;
  }

  if (autonomous == false)
  {
    dtmf_values();
    Serial.print("DTMF Number   ");
    Serial.println(dtmf_no);
  }
}

void dtmf_values()
{
  int digit=0, number=0;
  double result = 0.0;
  long int decimal_place = 10;
//  Stop();
  if (dtmf_no == 2)
  {
    f++;  b = 0;  l = 0;  r = 0;
    forward(f);
  }
  else if (dtmf_no == 4)
  {
    f = 0;  b = 0;  l = 0;  r++;
    right(r);
  }
  else if (dtmf_no == 6)
  {
    f = 0;  b = 0;  l++;  r = 0;
    left(l);
  }
  else if (dtmf_no == 8)
  {
    f = 0;  b++;  l = 0;  r = 0;
    backward(b);
  }
  else if (dtmf_no == 5)
  {
    f = 0;  b = 0;  l = 0;  r = 0;
    Stop();
  }
  else if (dtmf_no == 0)    //autonomous mode
  {
    bool after_dec = false;
    autonomous = true;
    for (int i = 1; i <= 2; i++)    //1 for dest latitude, 2 for dest longitude
    {
      while (1)
      {
        temp5 = digitalRead(D4);
        if (temp5 == 1)
        {
          dtmf();
          if (dtmf_no != 555 && dtmf_no != 999 && after_dec == false)  // number before decimal
          {
            number = number * 10 + dtmf_no;
            Serial.print(" Number  : ");
            Serial.println(number);
          }
          else if (dtmf_no == 999)
          {
            after_dec = true;
          }
          else if (dtmf_no != 555 && dtmf_no != 999 && after_dec == true)    // number after decimal
          {
            result += ((double) dtmf_no) / decimal_place;
            decimal_place *= 10;
            Serial.print(" \t");
            Serial.println(result, 8);
          }
          if (dtmf_no == 555 && temp5 == 1)    break;
        }
      }
      delay(300);
          result = result + number;
          Serial.print("Destination Latitude/Longitude :");
          Serial.print(" \t");
          Serial.println(result, 8);
          result = 0; number=0; decimal_place=10;
          after_dec = false;
      if (i == 1)  destLat = result;
      else  destLng = result;
    }
    autonomous_rover();
  }
  dtmf_no = 69;
//  Stop();
  if (f > 4) f = 4;
  if (b > 4) b = 4;
  if (l > 4) l = 4;
  if (r > 4) r = 4;
}
