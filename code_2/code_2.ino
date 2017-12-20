/*RR --> 0 towards ai
  LR --> 0 away ai
  all mid --> 180 up, 0 down
  all front --> 180 down, 0 up*/

#include<Servo.h>
Servo SR[9];
Servo SL[9];
//............R1,R2,R3,M1,M2,M3,F1, F2, F3
int SRA[9] = {90,90,90,80,75,80,90,90,100};
int SLA[9] = {90,90,90,90,70,95,90,95,95};
int FA = 0,i,j,k,l,m,n;
//variable FA is used to tell the position of moving forward
void setup()
{
  j = 52;
  k = 53;
  for(i=0 ; i<9 ; ++i)
  {
    SR[i].attach(j);
    SL[i].attach(k);
    j = j-2;
    k = k-2;
  }
}

void loop()
{
  //startingCalibrate();
  calibrate();
  delay(5000);
  //pushUps(5);
  //delay(1000);
  //twisting1();
  //delay(1000);
  //leftTurn(15);
  //delay(1000);
  rightTurn(3);
  //delay(1000);
  //meanToDown();
  //delay(200);
  //meanToDown();
  //forward(7);
  //downToMean();
  //delay(1000);
  //bent();
  //delay(1000);
  //gun_start(10);
  //delay(250);
  /*leftTurn(3);
  gun();
  leftTurn(3);
  gun();
  forward(2);
  gun();*/
  while(1);
}

void startingCalibrate()
{
  //Rear motors gain mean position
  for(i=0 ; i<=2 ; ++i)
  {
    SR[i].write(SRA[i]);
    SL[i].write(SLA[i]);
  }
  //mid motors move 90 up
  for(i=3 ; i<=5 ; ++i)
  {
    SR[i].write(SRA[i]+90);
    SL[i].write(SLA[i]+90);
  }
  //front gets alligned to 45 with mid
  for(i=6 ; i<=8 ; ++i)
  {
    SR[i].write(SRA[i]+45);
    SL[i].write(SLA[i]+45);
  }
  delay(1000);
  //legs straight forward, mid goes to mean and front 90 up from mean[+45 to -90]
  for(j=1 ; j<=90 ; ++j)
  {
    for(i=3 ; i<=5 ; ++i)
    {
      SR[i].write(SRA[i]+90-j);
      SL[i].write(SLA[i]+90-j);
    }
    for(i=6 ; i<=8 ; ++i)
    {
      SR[i].write(SRA[i]+45-3*j/2);
      SL[i].write(SLA[i]+45-3*j/2);
    }
    delay(10);
  }
  //all arms up, mid again moves 90 up
  for(j=1 ; j<=90 ; ++j)
  {
    for(i=3 ; i<=5 ; ++i)
    {
      SR[i].write(SRA[i]+j);
      SL[i].write(SLA[i]+j);
    }
    delay(10);
  }
  //position to get calibrated
  //front gets aligned to 45 with mid, mid moves slightly down
  //thus takes the position from which it will raise it self
  for(j=1 ; j<=45 ; ++j)
  {
    for(i=3 ; i<=5 ; ++i)
    {
      SR[i].write(SRA[i]+90-2*j/27);
      SL[i].write(SLA[i]+90-2*j/27);
    }
    for(i=6 ; i<=8 ; ++i)
    {
      SR[i].write(SRA[i]-90+3*j);
      SL[i].write(SLA[i]-90+3*j);
    }
    delay(10);
  }
  //final calibration
  for(j=1 ; j<=45 ; ++j)
  {
    for(i=3 ; i<=5 ; ++i)
    {
      SR[i].write(SRA[i]+80-16*j/9);
      SL[i].write(SLA[i]+80-16*j/9);
    }
    for(i=6 ; i<=8 ; ++i)
    {
      SR[i].write(SRA[i]+45-j);
      SL[i].write(SLA[i]+45-j);
    }
    delay(20);
  }
  //final position
  //picks opposite legs up, align front to mean(if slight mechanical error)and puts it down
  for(j=3 ; j<=5 ; ++j)
  {
    for(i=1 ; i<=30 ; ++i)
    {
      SR[j].write(SRA[j]+i);
      SL[8-j].write(SLA[8-j]+i);
      delay(10);
    }
    for(i=6 ; i<=8 ; ++i)
    {
      SR[i].write(SRA[i]);
      SL[i].write(SLA[i]);
    }
    for(i=1 ; i<=30 ; ++i)
    {
      SR[j].write(SRA[j]+30-i);
      SL[8-j].write(SLA[8-j]+30-i);
      delay(10);
    }
  }
}

void calibrate()
{
  for(i=0 ; i<9 ; ++i)
  {
    SR[i].write(SRA[i]);
    SL[i].write(SLA[i]);
    delay(50);
  }
}

//mean to up
void meanToUp()
{
  for(i=1 ; i<=45 ; ++i)
  {
    for(j=3 ; j<9 ; ++j)
    {
      SR[j].write(SRA[j]-i);
      SL[j].write(SLA[j]-i);
    }
    delay(15);
  }
  FA = -45;
}

void meanToDown()
{
  for(i=1 ; i<=45 ; ++i)
  {
    for(j=3 ; j<9 ; ++j)
    {
      SR[j].write(SRA[j]+i);
      SL[j].write(SLA[j]+i);
    }
    delay(15);
  }
  FA = 45;
}

void pushUps(int x)
{
  meanToUp();
  //continuous pushups
  while(1)
  {
    //neeche aa raha hai
    for(i=-45 ; i<=45 ; ++i)
    {
      for(j=3 ; j<9 ; ++j)
      {
        SR[j].write(SRA[j]+i);
        SL[j].write(SLA[j]+i);
      }
      delay(10);
    }
    FA = 45;
    //oopar ja raha hai
    for(i=45 ; i>=-45 ; --i)
    {
      for(j=3 ; j<9 ; ++j)
      {
        SR[j].write(SRA[j]+i);
        SL[j].write(SLA[j]+i);
      }
      delay(15);
    }
    FA = -45;
    --x;
    if(x == 0)break;
  }
  upToMean();
}

void upToMean()
{
  for(i=1 ; i<=45 ; ++i)
  {
    for(j=3 ; j<9 ; ++j)
    {
      SR[j].write(SRA[j]-45+i);
      SL[j].write(SLA[j]-45+i);
    }
    delay(15);
  }
  FA = 0;
}

void downToMean()
{
  for(i=1 ; i<=45 ; ++i)
  {
    for(j=3 ; j<9 ; ++j)
    {
      SR[j].write(SRA[j]+45-i);
      SL[j].write(SLA[j]+45-i);
    }
    delay(15);
  }
  FA = 0;
}

void twisting1()
{
  for(i=1 ; i<=60 ; ++i)
  {
    for(j=0 ; j<=2 ; ++j)
    {
      SR[j].write(SRA[j]-i);
      SL[j].write(SLA[j]-i);
    }
    delay(5);
  }
  delay(500);
  for(k=1 ; k<=2 ; ++k)
  {
    for(i=-60 ; i<=60 ; ++i)
    {
      for(j=0 ; j<=2 ; ++j)
      {
        SR[j].write(SRA[j]+i);
        SL[j].write(SLA[j]+i);
      }
      delay(5);
    }
    delay(500);
    for(i=60 ; i>=-60; --i)
    {
      for(j=0 ; j<=2 ; ++j)
      {
        SR[j].write(SRA[j]+i);
        SL[j].write(SLA[j]+i);
      }
      delay(5);
    }
    delay(500);
  }
  for(i=-60 ; i<=0 ; ++i)
  {
    for(j=0 ; j<=2 ; ++j)
    {
      SR[j].write(SRA[j]+i);
      SL[j].write(SLA[j]+i);
    }
    delay(5);
  }
}

void leftTurn(int x)
{
  //start turning left
  //SET1[R1 R3 L2]
  for(i=1 ; i<=30 ; ++i)
  {
    if(i<=15)SR[3].write(SRA[3]+i);
    else if(i>15)SR[3].write(SRA[3]-i+30);
    
    if(i<=15)SR[5].write(SRA[5]+i);
    else if(i>15)SR[5].write(SRA[5]-i+30);
    
    if(i<=15)SL[4].write(SLA[4]+i);
    else if(i>15)SL[4].write(SLA[4]-i+30);
    
    if(i==15)
    {
      for(l=1 ; l<=45 ; ++l)
      { 
        SR[0].write(SRA[0]-l);
        SR[2].write(SRA[2]-l);
        SL[1].write(SLA[1]-l);
        delay(10);
      }
    }
    delay(10);
  }
  //continue turning now
  while(1)
  {
    //set2[R2 L1 L3] move 45 left, set1 will come to mean
    for(i=1 ; i<=30 ; ++i)
    {
      if(i<=15)SR[4].write(SRA[4]+i);
      else if(i>15)SR[4].write(SRA[4]-i+30);
      
      if(i<=15)SL[3].write(SLA[3]+i);
      else if(i>15)SL[3].write(SLA[3]-i+30);
      
      if(i<=15)SL[5].write(SLA[5]+i);
      else if(i>15)SL[5].write(SLA[5]-i+30);
      
      if(i==15)
      {
        for(l=1 ; l<=45 ; ++l)
        {
          SL[2].write(SLA[2]-l);
          SL[0].write(SLA[0]-l);
          SR[1].write(SRA[1]-l);
      
          SR[0].write(SRA[0]-45+l);
          SR[2].write(SRA[2]-45+l);
          SL[1].write(SLA[1]-45+l);
          delay(10);
        }
      }
      delay(10);
    }
    --x;
    if(x == 1)break;
    //SET1 moves and set2 comes to mean
    for(i=1 ; i<=30 ; ++i)
    {
      if(i<=15)SR[3].write(SRA[3]+i);
      else if(i>15)SR[3].write(SRA[3]-i+30);
      
      if(i<=15)SR[5].write(SRA[5]+i);
      else if(i>15)SR[5].write(SRA[5]-i+30);
      
      if(i<=15)SL[4].write(SLA[4]+i);
      else if(i>15)SL[4].write(SLA[4]-i+30);
      
      if(i==15)
      {
        for(l=1 ; l<=45 ; ++l)
        {
          SL[1].write(SLA[1]-l);
          SR[2].write(SRA[2]-l);
          SR[0].write(SRA[0]-l);
      
          SR[1].write(SRA[1]-45+l);
          SL[0].write(SLA[0]-45+l);
          SL[2].write(SLA[2]-45+l);
          delay(10);
        }
      }
      delay(10);
    }
    --x;
    if(x == 1)break;
  }
  //end step set2 up-down, set1 to mean
  for(i=1 ; i<=30; ++i)
  {
    if(i<=15)SR[4].write(SRA[4]+i);
    else if(i>15)SR[4].write(SRA[4]-i+30);
    
    if(i<=15)SL[3].write(SLA[3]+i);
    else if(i>15)SL[3].write(SLA[3]-i+30);
     
    if(i<=15)SL[5].write(SLA[5]+i);
    else if(i>15)SL[5].write(SLA[5]-i+30);
    
    if(i == 15)
    {
      for(l=1 ; l<=45 ; ++l)
      {
        SL[1].write(SLA[1]-45+l);
        SR[0].write(SRA[0]-45+l);
        SR[2].write(SRA[2]-45+l);
        delay(10);
      }
    }
    delay(10);
  }
}

void rightTurn(int x)
{
  //starting step
  //set1[L1 L3 R2] moves 45 right
  for(i=1 ; i<=30 ; ++i)
  {
    if(i<=15)SR[4].write(SRA[4]+i);
    else if(i>15)SR[4].write(SRA[4]-i+30);
    
    if(i<=15)SL[3].write(SLA[3]+i);
    else if(i>15)SL[3].write(SLA[3]-i+30);
    
    
    if(i<=15)SL[5].write(SLA[5]+i);
    else if(i>15)SL[5].write(SLA[5]-i+30);
    
    if(i == 15)
    {
      for(l=1 ; l<=45; ++l)
      {
        SL[2].write(SLA[2]+l);
        SR[1].write(SRA[1]+l);
        SL[0].write(SLA[0]+l);
        delay(10);
      }
    }
    delay(10);
  }
  //steps continue
  while(1)
  {
    //SET2 [R1 R3 L2] moves 45 right, set1 to mean
    for(i=1 ; i<=30 ; ++i)
    {
      if(i<=15)SR[3].write(SRA[3]+i);
      else if(i>15)SR[3].write(SRA[3]-i+30);
      
      if(i<=15)SL[4].write(SLA[4]+i);
      else if(i>15)SL[4].write(SLA[4]-i+30);
      
      if(i<=15)SR[5].write(SLA[5]+i);
      else if(i>15)SR[5].write(SRA[5]-i+30);
      
      if(i == 15)
      {
        for(l=1 ; l<=45 ; ++l)
        {
          SR[2].write(SRA[2]+l);
          SR[0].write(SRA[0]+l);
          SL[1].write(SLA[1]+l);
      
          SL[0].write(SLA[0]+45-l);
          SL[2].write(SLA[2]+45-l);
          SR[1].write(SRA[1]+45-l);
          delay(10);
        }
      }
      delay(10);
    }
    x--;
    if(x == 1) break;
    //SET1 45 right, set2 to mean
    for(i=1 ; i<=30 ; ++i)
    {
      if(i<=15)SR[4].write(SRA[4]+i);
      else if(i>15)SR[4].write(SRA[4]-i+30);
      
      if(i<=15)SL[5].write(SLA[5]+i);
      else if(i>15)SL[5].write(SLA[5]-i+30);
      
      if(i<=15)SL[3].write(SLA[3]+i);
      else if(i>15)SL[3].write(SLA[3]-i+30);
      
      if(i == 15)
      {
        for(l=1 ; l<=45 ; ++l)
        {
          SL[2].write(SLA[2]+l);
          SL[0].write(SLA[0]+l);
          SR[1].write(SRA[1]+l);
      
          SR[0].write(SRA[0]+45-l);
          SL[1].write(SLA[1]+45-l);
          SR[2].write(SRA[2]+45-l);
          delay(10);
        }
      }
      delay(10);
    }
    x--;
  if (x == 1) break;
  }
  //end step
  //set2 up-down, set1 to mean
  for(i=1 ; i<=30; ++i)
  {
    if(i<=15)SR[3].write(SRA[3]+i);
    else if(i>15)SR[3].write(SRA[3]-i+30);
      
    if(i<=15)SR[5].write(SRA[5]+i);
    else if(i>15)SR[5].write(SRA[5]-i+30);
      
    if(i<=15)SL[4].write(SLA[4]+i);
    else if(i>15)SL[4].write(SLA[4]-i+30);
    
    if(i == 15)
    {
      for(l=1 ; l<=45 ; ++l)
      {
        SL[2].write(SLA[2]+45-l);
        SL[0].write(SLA[0]+45-l);
        SR[1].write(SRA[1]+45-l);
        delay(10);
      }
    }
    delay(10);
  }
}

void forward(int x)
{
  //the legs r1,r3,l1 and l3 will swipe 45 and r2 and l2 will swipe 60
  //starting step (RR1=+15 , RR3=-60 , LR2=+30)
  for(j=1 ; j<=30 ; ++j)
  {
    if(j<=15)SR[5].write(SRA[5]+FA+j);
    else SR[5].write(SRA[5]+FA+30-j);
    
    if(j<=15)SL[4].write(SLA[4]+FA+j);
    else SL[4].write(SLA[4]+FA+30-j);
    
    if(j<=15)SR[3].write(SRA[3]+FA+j);
    else SR[3].write(SRA[3]+FA+30-j);
    
    if(j==15)
    {
      for(i=1 ; i<=60 ; ++i)
      {
        SR[2].write(SRA[2]-i);
        SL[1].write(SLA[1]+i/2);
        SR[0].write(SRA[0]+i/4);
        delay(10);
      }
    }
    delay(15);
  }
  //step1: set1[r1 r3 l2] will move back (away from the eye) and set2[r2 l1 l3] will move in front to angles[-30 -15 +60]
  for(j=1 ; j<=30 ; ++j)
  {
    if(j<=15)SL[5].write(SLA[5]+FA+j);
    else SL[5].write(SLA[5]+FA+30-j);
    
    if(j<=15)SR[4].write(SRA[4]+FA+j);
    else SR[4].write(SRA[4]+FA+30-j);
    
    if(j<=15)SL[3].write(SLA[3]+FA+j);
    else SL[3].write(SLA[3]+FA+30-j);
    
    if(j==15)
    {
      for(i=1 ; i<=60 ; ++i)
      {
        SR[2].write(SRA[2]-60+3*i/4);
        SL[1].write(SLA[1]+30-i);
        SR[0].write(SRA[0]+15+3*i/4);
        
        SL[2].write(SLA[2]+i);
        SR[1].write(SRA[1]-i/2);
        SL[0].write(SLA[0]-i/4);
        delay(10);
      }
    }
    delay(15);
  }
  --x;
  //continuous steps
  while(x!=0)
  {
    for(j=1 ; j<=30 ; ++j)
    {
      if(j<=15)SR[5].write(SRA[5]+FA+j);
      else SR[5].write(SRA[5]+FA+30-j);
      
      if(j<=15)SL[4].write(SLA[4]+FA+j);
      else SL[4].write(SLA[4]+FA+30-j);
      
      if(j<=15)SR[3].write(SRA[3]+FA+j);
      else SR[3].write(SRA[3]+FA+30-j);
      
      if(j==15)
      {
        for(i=1 ; i<=60 ; ++i)
        {
          
          SR[2].write(SRA[2]-15-3*i/4);
          SL[1].write(SLA[1]-30+i);
          SR[0].write(SRA[0]+60-3*i/4);
          
          SL[2].write(SLA[2]+60-3*i/4);
          SR[1].write(SRA[1]-30+i);
          SL[0].write(SLA[0]-15-3*i/4);
          delay(10);
        }
      }
      delay(15);
    }
    --x;
    if(x==0)break;
    for(j=1 ; j<=30 ; ++j)
    {
      if(j<=15)SL[5].write(SLA[5]+FA+j);
      else SL[5].write(SLA[5]+FA+30-j);
      
      if(j<=15)SR[4].write(SRA[4]+FA+j);
      else SR[4].write(SRA[4]+FA+30-j);
      
      if(j<=15)SL[3].write(SLA[3]+FA+j);
      else SL[3].write(SLA[3]+FA+30-j);
      
      if(j==15)
      {
        for(i=1 ; i<=60 ; ++i)
        {
          SR[2].write(SRA[2]-60+3*i/4);
          SL[1].write(SLA[1]+30-i);
          SR[0].write(SRA[0]+15+3*i/4);
          
          SL[2].write(SLA[2]+15+3*i/4);
          SR[1].write(SRA[1]+30-i);
          SL[0].write(SLA[0]-60+3*i/4);
          delay(10);
        }
      }
      delay(15);
    }
    --x;
    if(x==0)break;
  }
  delay(2500);
  //end arrangements
  //first r1 and l3 will go to mean position, first there mid will rise and then rear will gain the mean position and then mids will fall
  for(j=1 ; j<=15 ; ++j)
  {
    SR[3].write(SRA[3]+FA+j);
    SL[5].write(SLA[5]+FA+j);
    delay(15);
  }
  for(i=1 ; i<=60 ; ++i)
  {
    SR[0].write(SRA[0]+60-i);
    SL[2].write(SLA[2]+60-i);
    delay(10);
  }
  for(j=-14 ; j<=0 ; ++j)
  {
    SR[3].write(SRA[3]+FA-j);
    SL[5].write(SLA[5]+FA-j);
    delay(15);
  }
  //first r2 and l2 will go to mean position, first there mid will rise and then rear will gain the mean position
  for(j=1 ; j<=15 ; ++j)
  {
    SR[4].write(SRA[4]+FA+j);
    SL[4].write(SLA[4]+FA+j);
    delay(15);
  }
  for(i=1 ; i<=30 ; ++i)
  {
    SR[1].write(SRA[1]-30+i);
    SL[1].write(SLA[1]-30+i);
    delay(10);
  }
  for(j=-14 ; j<=0 ; ++j)
  {
    SR[4].write(SRA[4]+FA-j);
    SL[4].write(SLA[4]+FA-j);
    delay(15);
  }
  //first r1 and l3 will go to mean position, first there mid will rise and then rear will gain the mean position
  for(j=1 ; j<=15 ; ++j)
  {
    SR[5].write(SRA[5]+FA+j);
    SL[3].write(SLA[3]+FA+j);
    delay(15);
  }
  for(i=1 ; i<=15 ; ++i)
  {
    SR[2].write(SRA[2]-15+i);
    SL[0].write(SLA[0]-15+i);
    delay(10);
  }
  for(j=-14 ; j<=0 ; ++j)
  {
    SR[5].write(SRA[5]+FA-j);
    SL[3].write(SLA[3]+FA-j);
    delay(15);  
   }
}


/*void bent()
{
  //step1
  for(i=1 ; i<=45 ; ++i)
  {
    SR[6].write(SRA[6]+i);
    SR[3].write(SRA[3]+i);
  
    SL[6].write(SLA[6]+i);
    SL[3].write(SLA[3]+i);
  
    SR[5].write(SRA[5]-i);
    SR[8].write(SRA[8]-i);
  
    SL[5].write(SLA[5]-i);
    SL[8].write(SLA[8]-i);
    delay(5);
  }
  for(k=1 ; k<=5 ; ++k)
  {
    //step2
    for(i=1 ; i<=25 ; ++i)
    {
      SR[4].write(SRA[4]+4*i/5);//RM2
      SR[7].write(SRA[7]+4*i/5);//RF2
      SL[3].write(SLA[3]+45-i);//LM1
      SL[6].write(SLA[6]+45-i);//LF1
      SR[5].write(SRA[5]-45+i);//RM3
      SR[8].write(SRA[8]-45+i);//RF3
      SL[4].write(SLA[4]-4*i/5);//LM2
      SL[7].write(SLA[7]-4*i/5);//LF2
      delay(5);
    }
    //step3
    for(i=1 ; i<=25 ; ++i)
    {
      SR[4].write(SRA[4]+20+i);//RM2
      SR[7].write(SRA[7]+20+i);//RF2
      SL[3].write(SLA[3]+20-4*i/5);//LM1
      SL[6].write(SLA[6]+20-4*i/5);//LF1
      SR[5].write(SRA[5]-20+4*i/5);//RM3
      SR[8].write(SRA[8]-20+4*i/5);//RF3
      SL[4].write(SLA[4]-20-i);//LM2
      SL[7].write(SLA[7]-20-i);//LF2
      delay(5);
    }
    //step4
    for(i=1 ; i<=25 ; ++i)
    {
      SL[3].write(SLA[3]-4*i/5);//LM1
      SL[6].write(SLA[6]-4*i/5);//LF1
      SR[5].write(SRA[5]+4*i/5);//RM3
      SR[8].write(SRA[8]+4*i/5);//RF3
      SR[3].write(SRA[3]+45-i);//RM1
      SR[6].write(SRA[6]+45-i);//RF1
      SL[5].write(SLA[5]-45+i);//LM3
      SL[8].write(SLA[8]-45+i);//LF3
      delay(5);
    }
    //step5
    for(i=1 ; i<=25 ; ++i)
    {
      SL[3].write(SLA[3]-20-i);//LM1
      SL[6].write(SLA[6]-20-i);//LF1
      SR[5].write(SRA[5]+20+i);//RM3
      SR[8].write(SRA[8]+20+i);//RF3
      SR[3].write(SRA[3]+20-4*i/5);//RM1
      SR[6].write(SRA[6]+20-4*i/5);//RF1
      SL[5].write(SLA[5]-20+4*i/5);//LM3
      SL[8].write(SLA[8]-20+4*i/5);//LF3
      delay(5);
    }
    //step6
    for(i=1 ; i<=25 ; ++i)
    {
      SR[4].write(SRA[4]+45-i);//RM2
      SR[7].write(SRA[7]+45-i);//RF2
      SL[4].write(SLA[4]-45+i);//LM2
      SL[7].write(SLA[7]-45+i);//LF2
      SR[3].write(SRA[3]-4*i/5);//RM1
      SR[6].write(SRA[6]-4*i/5);//RF1
      SL[5].write(SLA[5]+4*i/5);//LM3
      SL[8].write(SLA[8]+4*i/5);//LF3
      delay(5);
    }
    //step7
    for(i=1 ; i<=25 ; ++i)
    {
      SR[4].write(SRA[4]+20-4*i/5);//RM2
      SR[7].write(SRA[7]+20-4*i/5);//RF2
      SL[4].write(SLA[4]-20+4*i/5);//LM2
      SL[7].write(SLA[7]-20+4*i/5);//LF2
      SR[3].write(SRA[3]-20-i);//RM1
      SR[6].write(SRA[6]-20-i);//RF1
      SL[5].write(SLA[5]+20+i);//LM3
      SL[8].write(SLA[8]+20+i);//LF3
      delay(5);
    }
    //step8
    for(i=1 ; i<=25 ; ++i)
    {
      SR[4].write(SRA[4]-4*i/5);//RM2
      SR[7].write(SRA[7]-4*i/5);//RF2
      SL[4].write(SLA[4]+4*i/5);//LM2
      SL[7].write(SLA[7]+4*i/5);//LF2
      SL[3].write(SLA[3]-45+i);//LM1
      SL[6].write(SLA[6]-45+i);//LF1
      SR[5].write(SRA[5]+45-i);//RM3
      SR[8].write(SRA[8]+45-i);//RF3
      delay(5);
    }
    //step9
    for(i=1 ; i<=25 ; ++i)
    {
      SR[4].write(SRA[4]-20-i);//RM2
      SR[7].write(SRA[7]-20-i);//RF2
      SL[4].write(SLA[4]+20+i);//LM2
      SL[7].write(SLA[7]+20+i);//LF2
      SL[3].write(SLA[3]-20+4*i/5);//LM1
      SL[6].write(SLA[6]-20+4*i/5);//LF1
      SR[5].write(SRA[5]+20-4*i/5);//RM3
      SR[8].write(SRA[8]+20-4*i/5);//RF3
      delay(5);
    }
    //step10
    for(i=1 ; i<=25 ; ++i)
    {
      SR[3].write(SRA[3]-45+i);//rm1
      SR[6].write(SRA[6]-45+i);//RF1
      SL[3].write(SLA[3]+4*i/5);//LM1
      SL[6].write(SLA[6]+4*i/5);//LF1
      SR[5].write(SRA[5]-4*i/5);//RM3
      SR[8].write(SRA[8]-4*i/5);//RF3
      SL[5].write(SLA[5]+45-i);//LM3
      SL[8].write(SLA[8]+45-i);//LF3
      delay(5);
    }
    //step11
    for(i=1 ; i<=25 ; ++i)
    {
      SR[3].write(SRA[3]-20+4*i/5);//rm1
      SR[6].write(SRA[6]-20+4*i/5);//RF1
      SL[3].write(SLA[3]+20+i);//LM1
      SL[6].write(SLA[6]+20+i);//LF1
      SR[5].write(SRA[5]-20-i);//RM3
      SR[8].write(SRA[8]-20-i);//RF3
      SL[5].write(SLA[5]+20-4*i/5);//LM3
      SL[8].write(SLA[8]+20-4*i/5);//LF3
      delay(5);
    }
    //step12
    for(i=1 ; i<=25 ; ++i)
    {
      SR[3].write(SRA[3]+4*i/5);//rm1
      SR[6].write(SRA[6]+4*i/5);//RF1
      SR[4].write(SRA[4]-45+i);//RM2
      SR[7].write(SRA[7]-45+i);//RF2
      SL[4].write(SLA[4]+45-i);//LM2
      SL[7].write(SLA[7]+45-i);//LF2
      SL[5].write(SLA[5]-4*i/5);//LM3
      SL[8].write(SLA[8]-4*i/5);//LF3
      delay(5);
    }
    //step1
    for(i=1 ; i<=25 ; ++i)
    {
      SR[3].write(SRA[3]+20+i);//rm1
      SR[6].write(SRA[6]+20+i);//RF1
      SR[4].write(SRA[4]-20+4*i/5);//RM2
      SR[7].write(SRA[7]-20+4*i/5);//RF2
      SL[4].write(SLA[4]+20-4*i/5);//LM2
      SL[7].write(SLA[7]+20-4*i/5);//LF2
      SL[5].write(SLA[5]-20-i);//LM3
      SL[8].write(SLA[8]-20-i);//LF3
      delay(5);
    }
  }
  calibrate();
}*/

void gun_start(int x)
{
  //r2 raised up and moved 45 towards eye
  for(i=1 ; i<=15 ; ++i)
  {
    SR[4].write(SRA[4]+i);
    delay(10);
  }
  for(i=1 ; i<=45 ; ++i)
  {
    SR[1].write(SRA[1]-i);
    delay(15);
  }
  for(i=14 ; i>=0 ; --i)
  {
    SR[4].write(SRA[4]+i);
    delay(10);
  }
  //l2 raised up and moved 45 towards eye
  for(i=1 ; i<=15 ; ++i)
  {
    SL[4].write(SLA[4]+i);
    delay(10);
  }
  for(i=1 ; i<=45 ; ++i)
  {
    SL[1].write(SLA[1]+i);
    delay(15);
  }
  for(i=14 ; i>=0 ; --i)
  {
    SL[4].write(SLA[4]+i);
    delay(10);
  }
  //tilting of the chassis towards r3 and l3
  for(i=1 ; i<=45 ; ++i)
  {
    SR[5].write(SRA[5]+i);
    SR[8].write(SRA[8]+i);
    SL[5].write(SLA[5]+i);
    SL[8].write(SLA[8]+i);
    SR[4].write(SRA[4]-2*i/3);
    SR[7].write(SRA[7]-2*i/3);
    SL[4].write(SLA[4]-2*i/3);
    SL[7].write(SLA[7]-2*i/3);
    delay(15);
  }
  //r1 and l1 made parallel to each other
  for(i=1 ; i<=30 ; ++i)
  {
    SR[0].write(SRA[0]-i);
    SL[0].write(SLA[0]+i);
    delay(15);
  }
  //rf1 and lf1 raised for straight arms
  for(i=1 ; i<=80 ; ++i)
  {
    SR[6].write(SRA[6]-i);
    SL[6].write(SLA[6]-i);
    delay(15);
  }
  //gun starts shooting (r1 up, l1 down)
  for(i=1 ; i<=15 ; i++)
  {
    SR[3].write(SRA[3]+i);
    SL[3].write(SLA[3]-i);
    delay(5);
  }
  while(1)
  {
    //set1: r1 moves down, l1 moves up
    for(i=1 ; i<=30 ; i++)
    {
      SR[3].write(SRA[3]+15-i);
      SL[3].write(SLA[3]-15+i);
      delay(5);
    }
    x--;
    if (x == 0){gun_end(1); break;}
    //set2: r1 moves up, l1 down
    for(i=1 ; i<=30 ; i++)
    {
      SR[3].write(SRA[3]-15+i);
      SL[3].write(SLA[3]+15-i);
      delay(5);
    }
    x--;
    if (x == 0) {gun_end(2); break;}
  }
}
void gun_end(int a)
{
  for(i=1 ; i<=15 && a==2 ; ++i)
  {
    SR[3].write(SRA[3]+15-i);
    SL[3].write(SLA[3]-15+i);
    delay(5);
  }
  for(i=1 ; i<=15 && a==1; ++i)
  {
    SL[3].write(SLA[3]+15-i);
    SR[3].write(SRA[3]-15+i);
    delay(5);
  }
  //r1 and l1 moves apart from each other
  for(i=1 ; i<=30 ; ++i)
  {
    SR[0].write(SRA[0]-30+i);
    SL[0].write(SLA[0]+30-i);
    delay(15);
  }
  //rf1 and lf1 move 80 down
  for(i=1 ; i<=80 ; ++i)
  {
    SR[6].write(SRA[6]+80-i); 
    SL[6].write(SLA[6]+80-i);
    delay(15);
  }
//flat position recovery
  for(i=1 ; i<=45 ; ++i)
  {
    SR[5].write(SRA[5]+45-i);
    SR[8].write(SRA[8]+45-i);
    SL[5].write(SLA[5]+45-i);
    SL[8].write(SLA[8]+45-i);
    SR[4].write(SRA[4]-30+2*i/3);
    SR[7].write(SRA[7]-30+2*i/3);
    SL[4].write(SLA[4]-30+2*i/3);
    SL[7].write(SLA[7]-30+2*i/3);
    delay(15);
  }
//beech wale legs
//r2 to mean position
  for(i=1 ; i<=15 ; ++i)
  {
    SR[4].write(SRA[4]+i);
    delay(10);
  }
  for(i=1 ; i<=45 ; ++i)
  {
    SR[1].write(SRA[1]-45+i);
    delay(15);
  }
  for(i=14 ; i>=0 ; --i)
  {
    SR[4].write(SRA[4]+i);
    delay(10);
  }
  //L2 moves to mean
  for(i=1 ; i<=15 ; ++i)
  {
    SL[4].write(SLA[4]+i);
    delay(10);
  }
  for(i=1 ; i<=45 ; ++i)
  {
    SL[1].write(SLA[1]+45-i);
    delay(15);
  }
  for(i=14 ; i>=0 ; --i)
  {
    SL[4].write(SLA[4]+i);
    delay(10);
  }
  calibrate();
}
