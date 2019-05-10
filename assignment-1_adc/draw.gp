cd 'data'

# write plot to file
set terminal png size 800,600

# digram labeling
set ylabel "voltage (volts)"
set xlabel "time (s)"
set y2label "current (ampere)"

#set linestyles 
set style line 1 lt 1 lw 1 pt 1 linecolor rgb "red"
set style line 2 lt 1 lw 1 pt 1 linecolor rgb "blue"
set style line 3 lt 1 lw 1 pt 1 linecolor rgb "orange"

set ytics nomirror
set y2tics
set tics out
set autoscale  y
set autoscale y2
set grid x y2
# set the position of the legend:
set key right center


#plot only with points
set output 'rc_charging_curve_voltage_current.png'
plot 'f_charge_voltage.log' axes x1y1 title 'voltage' ls 2, 'f_charge_current.log' axes x1y2 title 'charging curve of a capacitor' ls 1

set output 'rc_discharging_curve_voltage_current.png'
plot 'f_discharge_voltage.log' axes x1y1 title 'voltage' ls 2, 'f_discharge_current.log' axes x1y2 title 'discharging curve of a capacitor' ls 1