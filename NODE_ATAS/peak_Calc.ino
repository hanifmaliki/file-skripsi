void peak_calc(void)
{
  if (abs(inc_angle)>inc_angle_peak) inc_angle_peak=abs(inc_angle);
}

void peak_reset(void)
{
  inc_angle_peak = 0;
}
