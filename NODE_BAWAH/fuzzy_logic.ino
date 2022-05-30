void fuzzy_start(void)
{
  pga_dr1 = pga/drift_ratio_peak;

  x=pga_dr1; a=0.0030; b=0.0897; c=0.1703; d=0.5751;

  if (x>=0&&x<=a) {sig[0] = (a-x)/(a);} // SIG 0
  else if (x>=a) {sig[0] = 0;}

  if (x>=0&&x<=a) {sig[1] = x/a;} // SIG I
  else if (x>=a&&x<=b) {sig[1] = (b-x)/(b-a);}
  else if (x>=b) {sig[1] = 0;}

  if (x<=a||x>=c) {sig[2] = 0;} // SIG II
  else if (x>=a&&x<=b) {sig[2] = (x-a)/(b-a);}
  else if (x>=b&&x<=c) {sig[2] = (c-x)/(c-b);}

  if (x<=b||x>=d) {sig[3] = 0;} // SIG III
  else if (x>=b&&x<=c) {sig[3] = (x-b)/(c-b);}
  else if (x>=c&&x<=d) {sig[3] = (d-x)/(d-c);}

  if (x<=c) {sig[4] = 0;} // SIG IV
  else if (x>=c&&x<=d) {sig[4] = (x-c)/(d-c);}
  else if (x>=d) {sig[4] = 1;}

  z0=0; z1=1; z2=2; z3=3; z4=4;

  score = (sig[0]*z0+sig[1]*z1+sig[2]*z2+sig[3]*z3+sig[4]*z4)
         /(sig[0]+sig[1]+sig[2]+sig[3]+sig[4]);
}

void fuzzy_reset(void)
{
  pga_dr1 = 0;
  score = 0;
}
