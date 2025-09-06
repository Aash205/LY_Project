
int forward(int f)
{
  analogWrite(m11, sp * f);
  analogWrite(m12, 0);
  analogWrite(m21, sp * f);
  analogWrite(m22, 0);
  Serial.print(sp * f);
  motion = true;
}

int backward(int b)
{
  analogWrite(m11, 0);
  analogWrite(m12, sp * b);
  analogWrite(m21, 0);
  analogWrite(m22, sp * b);
  Serial.print(sp * b);
  motion = true;
}

int only_right(int onr)
{
  analogWrite(m11, 0);
  analogWrite(m12, 0);
  analogWrite(m21, sp * onr);
  analogWrite(m22, 0);
  Serial.print(sp * onr);
  motion = true;
}

int only_left(int ol)
{
  analogWrite(m11, sp * ol);
  analogWrite(m12, 0);
  analogWrite(m21, 0);
  analogWrite(m22, 0);
  Serial.print(sp * ol);
  motion = true;
}

int left(int l)
{
  analogWrite(m11, sp * l);
  analogWrite(m12, 0);
  analogWrite(m21, 0);
  analogWrite(m22,  sp * l); //0
  Serial.print(sp * l);
  motion = true;
}

int right(int r)
{
  analogWrite(m11, 0);
  analogWrite(m12,  sp * r);   //0
  analogWrite(m21, sp * r);
  analogWrite(m22, 0);
  Serial.print(sp * r);
  motion = true;
}

void Stop()
{
  b = 0;  f = 0;  l = 0;  r = 0; onr = 0; ol = 0;
  analogWrite(m11, 0);
  analogWrite(m12, 0);
  analogWrite(m21, 0);
  analogWrite(m22, 0);
  motion = false;
}
