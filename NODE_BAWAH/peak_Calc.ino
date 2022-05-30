void peak_calc(void)
{
  if (abs(ground_acc)>pga) pga=abs(ground_acc);
  if (abs(inc_angle)>inc_angle_peak) inc_angle_peak=abs(inc_angle);
  if (abs(displacement)>displacement_peak) displacement_peak=abs(displacement);
  if (abs(drift_ratio)>drift_ratio_peak) drift_ratio_peak=abs(drift_ratio);
}

void peak_reset(void)
{
  pga = 0;
  inc_angle_peak = 0;
  displacement_peak = 0;
  drift_ratio_peak = 0;
}
