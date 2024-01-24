/*For the generator*/
const int Ns = 316;//number of samples
int sampling_interval;
byte samples[Ns];
float MGTS[Ns];
const float no_flow_int = 1.5;//amplitude of pumping in no flow
const byte GENERATIVE = 1;
const byte N = 40;//number of neurons
float buffer[N];
float Wouttmp[N+2];
const float Wout[N+2] = {4.028320E-03, 3.930664E-01, 5.468750E-02, 2.548218E-02, 2.099609E-02, -1.59607E-02,
                         -2.73438E-02, -5.77393E-02, -1.57715E-01, -1.53809E-01, -5.82275E-02, -4.41895E-02,
                         -2.19727E-03, 8.154297E-02, 1.401367E-01, 5.029297E-02, -2.44141E-03, 1.496582E-01,
                         2.929688E-02, -1.56250E-02, 3.808594E-02, 6.402588E-02, 2.239990E-02, 2.648926E-02,
                         4.876709E-02, 3.601074E-02, 2.392578E-02, 3.759766E-02, 2.508545E-02, -1.80664E-02,
                         -1.10779E-01, -1.68213E-01, -8.08105E-02, -1.28937E-02, 4.833984E-02, 1.064453E-01,
                         9.365845E-02, 8.837891E-02, 3.735352E-02, -2.38037E-02, -4.83398E-02, -1.16211E-01};
float predicted;
float t1, t2;
const int fs = 128; 
float dt;


/*For reading the signal*/
int sensorValue;
float voltage;

/*Pin numbers and other IO stuff*/
const int pinOut = 10;
float ard_time;
int buttonState = 0;  // variable for reading the pushbutton status
const int buttonPin = 2;  // the number of the pushbutton pin

// the setup routine runs once when you press reset:
void setup()
{

  // ESN
  Wouttmp[0] = 1.0;

  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  // the signal will be output to pin 10
  pinMode(pinOut, OUTPUT);//sets the digital pin 10 as output

  MGTS[0] = 0.122327;  MGTS[1] = 0.254046;  MGTS[2] = 0.287391;  MGTS[3] = 0.442596;  MGTS[4] = 0.049058;
  MGTS[5] = 0.319360;  MGTS[6] = 0.376547;  MGTS[7] = 0.282452;  MGTS[8] = 0.296585;  MGTS[9] = 0.498074;
  MGTS[10] = 0.378183;  MGTS[11] = 0.258849;  MGTS[12] = 0.333316;  MGTS[13] = 0.252820;  MGTS[14] = 0.024729;
  MGTS[15] = 0.046801;  MGTS[16] = 0.181542;  MGTS[17] = 0.169161;  MGTS[18] = 0.326087;  MGTS[19] = 0.596121;
  MGTS[20] = 0.743214;  MGTS[21] = 0.739563;  MGTS[22] = 0.735999;  MGTS[23] = 0.486970;  MGTS[24] = 0.029400;
  MGTS[25] = -0.365138;  MGTS[26] = -0.623344;  MGTS[27] = -0.768326;  MGTS[28] = -0.549657;  MGTS[29] = 0.013006;
  MGTS[30] = 0.298534;  MGTS[31] = 0.330912;  MGTS[32] = 0.283533;  MGTS[33] = 0.445606;  MGTS[34] = 0.622251;
  MGTS[35] = 0.500566;  MGTS[36] = 0.402967;  MGTS[37] = 0.369525;  MGTS[38] = 0.097444;  MGTS[39] = -0.210115;
  MGTS[40] = -0.276675;  MGTS[41] = -0.218654;  MGTS[42] = -0.088938;  MGTS[43] = 0.293623;  MGTS[44] = 0.573770;
  MGTS[45] = 0.743477;  MGTS[46] = 0.877435;  MGTS[47] = 0.960707;  MGTS[48] = 0.672890;  MGTS[49] = 0.172619;
  MGTS[50] = -0.283530;  MGTS[51] = -0.647304;  MGTS[52] = -0.897830;  MGTS[53] = -0.832491;  MGTS[54] = -0.246720;
  MGTS[55] = 0.160453;  MGTS[56] = 0.213002;  MGTS[57] = 0.101630;  MGTS[58] = 0.140621;  MGTS[59] = 0.463153;
  MGTS[60] = 0.561343;  MGTS[61] = 0.606047;  MGTS[62] = 0.733968;  MGTS[63] = 0.710153;  MGTS[64] = 0.324566;
  MGTS[65] = -0.022143;  MGTS[66] = -0.309306;  MGTS[67] = -0.587365;  MGTS[68] = -0.692306;  MGTS[69] = -0.313432;
  MGTS[70] = 0.189772;  MGTS[71] = 0.444375;  MGTS[72] = 0.450366;  MGTS[73] = 0.435879;  MGTS[74] = 0.646401;
  MGTS[75] = 0.597416;  MGTS[76] = 0.291896;  MGTS[77] = 0.101952;  MGTS[78] = -0.055315;  MGTS[79] = -0.354685;
  MGTS[80] = -0.441381;  MGTS[81] = -0.132244;  MGTS[82] = 0.256544;  MGTS[83] = 0.567529;  MGTS[84] = 0.678749;
  MGTS[85] = 0.743063;  MGTS[86] = 0.873035;  MGTS[87] = 0.658003;  MGTS[88] = 0.173608;  MGTS[89] = -0.229093;
  MGTS[90] = -0.549429;  MGTS[91] = -0.804353;  MGTS[92] = -0.760361;  MGTS[93] = -0.201051;  MGTS[94] = 0.222297;
  MGTS[95] = 0.319034;  MGTS[96] = 0.233050;  MGTS[97] = 0.272882;  MGTS[98] = 0.552880;  MGTS[99] = 0.536387;
  MGTS[100] = 0.446994;  MGTS[101] = 0.492439;  MGTS[102] = 0.392490;  MGTS[103] = 0.030989;  MGTS[104] = -0.161741;
  MGTS[105] = -0.211623;  MGTS[106] = -0.291250;  MGTS[107] = -0.131928;  MGTS[108] = 0.295017;  MGTS[109] = 0.593603;
  MGTS[110] = 0.772778;  MGTS[111] = 0.866980;  MGTS[112] = 0.951298;  MGTS[113] = 0.663084;  MGTS[114] = 0.145350;
  MGTS[115] = -0.315060;  MGTS[116] = -0.663910;  MGTS[117] = -0.905346;  MGTS[118] = -0.824171;  MGTS[119] = -0.223410;
  MGTS[120] = 0.161293;  MGTS[121] = 0.203291;  MGTS[122] = 0.091188;  MGTS[123] = 0.142703;  MGTS[124] = 0.468275;
  MGTS[125] = 0.566612;  MGTS[126] = 0.620926;  MGTS[127] = 0.750795;  MGTS[128] = 0.715899;  MGTS[129] = 0.322875;
  MGTS[130] = -0.030440;  MGTS[131] = -0.328182;  MGTS[132] = -0.609598;  MGTS[133] = -0.709686;  MGTS[134] = -0.322091;
  MGTS[135] = 0.184316;  MGTS[136] = 0.430053;  MGTS[137] = 0.426438;  MGTS[138] = 0.409394;  MGTS[139] = 0.626410;
  MGTS[140] = 0.592562;  MGTS[141] = 0.309451;  MGTS[142] = 0.145961;  MGTS[143] = 0.006373;  MGTS[144] = -0.298770;
  MGTS[145] = -0.404079;  MGTS[146] = -0.135172;  MGTS[147] = 0.215738;  MGTS[148] = 0.534679;  MGTS[149] = 0.685659;
  MGTS[150] = 0.765703;  MGTS[151] = 0.893521;  MGTS[152] = 0.725192;  MGTS[153] = 0.245216;  MGTS[154] = -0.189740;
  MGTS[155] = -0.535817;  MGTS[156] = -0.807551;  MGTS[157] = -0.829335;  MGTS[158] = -0.307232;  MGTS[159] = 0.164277;
  MGTS[160] = 0.288524;  MGTS[161] = 0.205691;  MGTS[162] = 0.199906;  MGTS[163] = 0.489616;  MGTS[164] = 0.556446;
  MGTS[165] = 0.499742;  MGTS[166] = 0.566756;  MGTS[167] = 0.543678;  MGTS[168] = 0.184851;  MGTS[169] = -0.090772;
  MGTS[170] = -0.232814;  MGTS[171] = -0.399256;  MGTS[172] = -0.403886;  MGTS[173] = 0.020499;  MGTS[174] = 0.418640;
  MGTS[175] = 0.643594;  MGTS[176] = 0.710643;  MGTS[177] = 0.793703;  MGTS[178] = 0.829625;  MGTS[179] = 0.436694;
  MGTS[180] = -0.033975;  MGTS[181] = -0.389630;  MGTS[182] = -0.680695;  MGTS[183] = -0.843725;  MGTS[184] = -0.528982;
  MGTS[185] = 0.040179;  MGTS[186] = 0.300011;  MGTS[187] = 0.288609;  MGTS[188] = 0.213890;  MGTS[189] = 0.412096;
  MGTS[190] = 0.587456;  MGTS[191] = 0.484662;  MGTS[192] = 0.459158;  MGTS[193] = 0.490339;  MGTS[194] = 0.218188;
  MGTS[195] = -0.097865;  MGTS[196] = -0.197243;  MGTS[197] = -0.256155;  MGTS[198] = -0.276342;  MGTS[199] = 0.077956;
  MGTS[200] = 0.455706;  MGTS[201] = 0.689692;  MGTS[202] = 0.818574;  MGTS[203] = 0.915938;  MGTS[204] = 0.868365;
  MGTS[205] = 0.417653;  MGTS[206] = -0.087855;  MGTS[207] = -0.491063;  MGTS[208] = -0.795193;  MGTS[209] = -0.931590;
  MGTS[210] = -0.557499;  MGTS[211] = 0.015190;  MGTS[212] = 0.217449;  MGTS[213] = 0.158713;  MGTS[214] = 0.074482;
  MGTS[215] = 0.305669;  MGTS[216] = 0.546069;  MGTS[217] = 0.577092;  MGTS[218] = 0.675153;  MGTS[219] = 0.774234;
  MGTS[220] = 0.532615;  MGTS[221] = 0.130535;  MGTS[222] = -0.175160;  MGTS[223] = -0.465813;  MGTS[224] = -0.693683;
  MGTS[225] = -0.562725;  MGTS[226] = -0.039629;  MGTS[227] = 0.352176;  MGTS[228] = 0.461013;  MGTS[229] = 0.410803;
  MGTS[230] = 0.515502;  MGTS[231] = 0.679307;  MGTS[232] = 0.444114;  MGTS[233] = 0.187261;  MGTS[234] = 0.064402;
  MGTS[235] = -0.180173;  MGTS[236] = -0.428980;  MGTS[237] = -0.310019;  MGTS[238] = 0.062251;  MGTS[239] = 0.413974;
  MGTS[240] = 0.646277;  MGTS[241] = 0.707991;  MGTS[242] = 0.830761;  MGTS[243] = 0.841475;  MGTS[244] = 0.445672;
  MGTS[245] = -0.027442;  MGTS[246] = -0.389505;  MGTS[247] = -0.695717;  MGTS[248] = -0.861212;  MGTS[249] = -0.549857;
  MGTS[250] = 0.026317;  MGTS[251] = 0.288491;  MGTS[252] = 0.270895;  MGTS[253] = 0.189494;  MGTS[254] = 0.384861;
  MGTS[255] = 0.577928;  MGTS[256] = 0.495734;  MGTS[257] = 0.490963;  MGTS[258] = 0.542672;  MGTS[259] = 0.283767;
  MGTS[260] = -0.048383;  MGTS[261] = -0.182749;  MGTS[262] = -0.288681;  MGTS[263] = -0.366072;  MGTS[264] = -0.048814;
  MGTS[265] = 0.370554;  MGTS[266] = 0.635417;  MGTS[267] = 0.763531;  MGTS[268] = 0.837756;  MGTS[269] = 0.898249;
  MGTS[270] = 0.536787;  MGTS[271] = 0.031372;  MGTS[272] = -0.381254;  MGTS[273] = -0.696174;  MGTS[274] = -0.896136;
  MGTS[275] = -0.679281;  MGTS[276] = -0.074387;  MGTS[277] = 0.226473;  MGTS[278] = 0.227286;  MGTS[279] = 0.126015;
  MGTS[280] = 0.266966;  MGTS[281] = 0.543371;  MGTS[282] = 0.549626;  MGTS[283] = 0.582404;  MGTS[284] = 0.684339;
  MGTS[285] = 0.517756;  MGTS[286] = 0.125042;  MGTS[287] = -0.138313;  MGTS[288] = -0.362245;  MGTS[289] = -0.572748;
  MGTS[290] = -0.468184;  MGTS[291] = 0.024971;  MGTS[292] = 0.411122;  MGTS[293] = 0.566049;  MGTS[294] = 0.558278;
  MGTS[295] = 0.664899;  MGTS[296] = 0.741736;  MGTS[297] = 0.398928;  MGTS[298] = 0.025760;  MGTS[299] = -0.220889;
  MGTS[300] = -0.493247;  MGTS[301] = -0.667225;  MGTS[302] = -0.383696;  MGTS[303] = 0.132430;  MGTS[304] = 0.451966;
  MGTS[305] = 0.511372;  MGTS[306] = 0.479788;  MGTS[307] = 0.653473;  MGTS[308] = 0.651998;  MGTS[309] = 0.306027;
  MGTS[310] = 0.035247;  MGTS[311] = -0.141740;  MGTS[312] = -0.424552;  MGTS[313] = -0.538208;  MGTS[314] = -0.199354;
  MGTS[315] = 0.251989;

  dt = 4.0 / (float) fs;   sampling_interval = (int) (dt/1.0e-6);//in microseconds
  for (k = 0; k < Ns; k++) 
  {
      samples[k] = (byte) (127.0*0.5 * MGTS[k] + 127.0*1.5);
  }
}

// the loop routine runs over and over again forever:
void loop()
{

 // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH)
  {
          //NO modulation
            for (int j = 0; j < Ns; j++)
            {
              ard_time = millis();   Serial.print(ard_time);   Serial.print(" ");    
              analogWrite(pinOut, 127.0*1.5);//send the generated signal to the pin
              Serial.print(127.0*no_flow_int / 254.0);   Serial.print(" ");

              // reading the reponse of the solitary-like waves
              sensorValue = analogRead(A0);   voltage = sensorValue * (5.0 / 1023.0);   Serial.println(voltage);

              delayMicroseconds(sampling_interval);
            }

          //sine waves for training
            for (int j = 0; j < Ns; j++)
            {
              ard_time = millis();   Serial.print(ard_time);   Serial.print(" ");    
              analogWrite(pinOut, samples[j]);//send the generated signal to the pin
              Serial.print((float) samples[j] / 254.0);   Serial.print(" ");

              // reading the reponse of the solitary-like waves
              sensorValue = analogRead(A0);   voltage = sensorValue * (5.0 / 1023.0);   Serial.println(voltage);
              buffer[j] = voltage;

              delayMicroseconds(sampling_interval);
            }

          //optional generative mode
          if (GENERATIVE != 0)
          {

              for (int j = 0; j < Ns; j++)
              {
                //continue generating the sine wave, output it to Serial but NOT to the pin 
                ard_time = millis();   Serial.print(ard_time);   Serial.print(" ");
                Serial.print((float) samples[j] / 254.0);   Serial.print(" ");
                
                t1 = millis();
                //reading the reponse of the solitary-like waves
                sensorValue = analogRead(A0);   voltage = sensorValue * (5.0 / 1023.0);   Serial.print(voltage);   Serial.print(" ");

                //update buffer
                for (int n = 0; n < N-1; n++)
                {
                    buffer[n] = buffer[n+1];
                };
                //buffer[N-1] = predicted;
                buffer[N-1] = voltage;

                //ESN, Wouttmp[0] was initialised above
                if (k == 0)
                {
                  predicted = (float) samples[j] / 254.0;//PREDICTIVE MODE when if is commented out
                }

                Wouttmp[1] = predicted/**0.95*/;

                for (int n = 0; n < N; n++)
                {
                    Wouttmp[2+n] = buffer[N-n];
                };

                //Readout
                predicted = 0.0;        
                for (int n = 0; n < N+2; n++) 
                {
                  predicted = predicted + Wout[n] * Wouttmp[n];
                }

                //write
                ard_time = millis();   Serial.print(ard_time);   Serial.print(" ");  Serial.println(predicted);
                analogWrite(pinOut, predicted);//send the generated signal to the pin    

                t2 = millis();
                delayMicroseconds(sampling_interval - (int)(abs(t2 - t1)*1.0e3));//!!! sampling_interval MAY NEED TO BE SMALLER TO COMPENSATE FOR THE DELAY CAUSED BY ESN CALCULATIONS

              }//j

          }//if GENERATIVE
  
  }
  else
  {
          //NO modulation
            for (int j = 0; j < Ns; j++)
            {
              ard_time = millis();   Serial.print(ard_time);   Serial.print(" ");    
              analogWrite(pinOut, 127.0*1.5);//send the generated signal to the pin
              Serial.print(127.0*no_flow_int / 254.0);   Serial.print(" ");

              // reading the reponse of the solitary-like waves
              sensorValue = analogRead(A0);   voltage = sensorValue * (5.0 / 1023.0);   Serial.println(voltage);

              delayMicroseconds(sampling_interval);
            }
  }//else pin2 switch

}

