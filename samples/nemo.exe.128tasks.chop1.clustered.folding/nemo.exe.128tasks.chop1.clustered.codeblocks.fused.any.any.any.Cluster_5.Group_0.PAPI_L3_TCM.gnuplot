X_LIMIT=58.64 # Do not touch this
FACTOR=1 # Do not touch this

set datafile separator ";";

# set term postscript eps solid color;
# set term pdfcairo solid color lw 2;
# set term png size 800,600;
# set term wxt size 800,600;

set multiplot title "Appl * Task * Thread * - Group_0 - Cluster_5\nDuration = 58.64 ms, Counter = 0.67 Mevents";

##############################
## Routines part 
##############################

samplecls(ret,r,g,t) = (r eq 'Cluster_5' && g == 0  && t eq 'cl') ? ret : NaN;

set size 1,0.15;
set origin 0,0.80;

set bmargin 0; set lmargin 14; set rmargin 17;

set xlabel "ghost" tc rgbcolor "white";
set ylabel "ghost" tc rgbcolor "white";
#set y2label "Code line";
set label 'Code line' at screen 0.975, screen 0.8+(0.175/2) rotate by -90 center;
set label "bottom" at second 1.005, first 0;
set label "top"    at second 1.005, first 1;
set xrange [0:X_LIMIT*1./FACTOR];
set x2range [0:1];
set yrange [0:1];
set y2range [0:*] reverse;
set ytics tc rgbcolor "white" (0.001) format "%0.2f";
set y2tics 100 tc rgbcolor "white" format "0000";
unset xtics;
unset x2tics;

set obj rect from graph 0.005*FACTOR, graph 0 to graph 0.057*FACTOR, graph 1 fs transparent solid 0.50 noborder fc rgbcolor '#B30200' behind # Routine: stp 5.155%
set obj rect from graph 0.057*FACTOR, graph 0 to graph 0.291*FACTOR, graph 1 fs transparent solid 0.50 noborder fc rgbcolor '#FFAC63' behind # Routine: iom__write_field3d 23.360%
set obj rect from graph 0.295*FACTOR, graph 0 to graph 0.380*FACTOR, graph 1 fs transparent solid 0.50 noborder fc rgbcolor '#500200' behind # Routine: iom__write_field2d 8.499%
set obj rect from graph 0.380*FACTOR, graph 0 to graph 0.413*FACTOR, graph 1 fs transparent solid 0.50 noborder fc rgbcolor '#641121' behind # Routine: dia_wri 3.336%
set obj rect from graph 0.413*FACTOR, graph 0 to graph 0.996*FACTOR, graph 1 fs transparent solid 0.50 noborder fc rgbcolor '#FFAC63' behind # Routine: iom__write_field3d 58.279%

# Summary for routine dia_wri 4.124%
# Summary for routine event__write_field2d 0.014%
# Summary for routine event__write_field3d 0.030%
# Summary for routine iom__write_field2d 8.499%
# Summary for routine iom__write_field3d 81.638%
# Summary for routine iom_p2d 0.013%
# Summary for routine iom_p3d 0.022%
# Summary for routine nemo 0.047%
# Summary for routine nemo_gcm 0.457%
# Summary for routine stp 5.155%

set label center "nemo >\nnemo_gcm >\nstp\n[188]" at second 0.031*FACTOR, graph 0.5 rotate by 90 tc rgbcolor 'black' front
set label center "iom_p3d >\nevent__write_field3d >\niom__write_field3d\n[374]" at second 0.174*FACTOR, graph 0.5 rotate by 90 tc rgbcolor 'black' front
set label center "iom_p2d >\nevent__write_field2d >\niom__write_field2d\n[304]" at second 0.337*FACTOR, graph 0.5 rotate by 90 tc rgbcolor 'black' front
set label center "nemo_gcm >\nstp >\ndia_wri\n[181]" at second 0.396*FACTOR, graph 0.5 rotate by 90 tc rgbcolor 'black' front
set label center "iom_p3d >\nevent__write_field3d >\niom__write_field3d\n[374]" at second 0.705*FACTOR, graph 0.5 rotate by 90 tc rgbcolor 'black' front

plot "nemo.exe.128tasks.chop1.clustered.codeblocks.fused.any.any.any.dump.csv" u ($4*FACTOR):(samplecls($5,strcol(2),$3,strcol(1))) with points axes x2y2 ti '' lc rgbcolor '#ff2090' pt 7 ps 0.5;

unset label; unset xlabel; unset x2label; unset ylabel; unset y2label;
unset xtics; unset x2tics; unset ytics; unset y2tics; set y2tics autofreq;
unset xrange; unset x2range; unset yrange; unset y2range;
unset tmargin; unset bmargin; unset lmargin; unset rmargin
unset label;
unset arrow;
unset obj;

set size 1,0.78;
set origin 0,0;
set tmargin 0; set lmargin 14; set rmargin 17;

set key bottom outside center horizontal samplen 1;
set x2range [0:1];
set yrange [0:1];
set y2range [0:*];
set ytics nomirror format "%.01f";
set y2tics nomirror format "%g";
#set x2tics nomirror format "%.02f";
set ylabel 'Normalized PAPI_L3_TCM';
set xlabel 'Time (ms)';
set xtics nomirror format "%.02f";
set xtics ( 0.0 , 1./5.*X_LIMIT, 2./5.*X_LIMIT, 3./5.*X_LIMIT, 4./5.*X_LIMIT, 5./5.*X_LIMIT, X_LIMIT/FACTOR);
set xrange [0:X_LIMIT*1./FACTOR];
set y2label 'PAPI_L3_TCM rate (in Mevents/s)';

# Mean rate
set label "" at first X_LIMIT*1./FACTOR, second 11.42 point pt 3 ps 2 lc rgbcolor "#707070";

# Breakpoints
# Unneeded phases separators, nb. breakpoints = 2

# Data accessors to CSV
sampleexcluded(ret,c,r,g,t) = (c eq 'PAPI_L3_TCM' && r eq 'Cluster_5' && g == 0  && t eq 'e') ? ret : NaN;
sampleunused(ret,c,r,g,t) = (c eq 'PAPI_L3_TCM' && r eq 'Cluster_5' && g ==  0 && t eq 'un') ? ret : NaN;
sampleused(ret,c,r,g,t) = (c eq 'PAPI_L3_TCM' && r eq 'Cluster_5' && g == 0 && t eq 'u') ? ret : NaN;
interpolation(ret,c,r,g) = (c eq 'PAPI_L3_TCM' && r eq 'Cluster_5' && g == 0 ) ? ret : NaN;
slope(ret,c,r,g) = (c eq 'PAPI_L3_TCM' && r eq 'Cluster_5' && g == 0 ) ? ret : NaN;

# Plot command
plot \
NaN ti 'Mean PAPI_L3_TCM rate' w points pt 3 lc rgbcolor "#707070" ,\
'nemo.exe.128tasks.chop1.clustered.codeblocks.fused.any.any.any.dump.csv' u ($4*FACTOR):(sampleexcluded($6, strcol(5), strcol(2), $3, strcol(1))) ti 'Excluded samples (936)' axes x2y1 w points pt 3 lc rgbcolor '#A0A0A0',\
'nemo.exe.128tasks.chop1.clustered.codeblocks.fused.any.any.any.dump.csv' u ($4*FACTOR):(sampleunused($6, strcol(5), strcol(2), $3, strcol(1))) ti 'Unused samples (336)' axes x2y1 w points pt 3 lc rgbcolor '#FFA0A0',\
'nemo.exe.128tasks.chop1.clustered.codeblocks.fused.any.any.any.dump.csv' u ($4*FACTOR):(sampleused($6, strcol(5), strcol(2), $3, strcol(1))) ti 'Used samples (1500)' axes x2y1 w points pt 3 lc rgbcolor '#FF0000',\
'nemo.exe.128tasks.chop1.clustered.codeblocks.fused.any.any.any.interpolate.csv' u ($4*FACTOR):(interpolation($5, strcol(3), strcol(1), $2)) ti 'Fitting [Kriger (nuget=1.0e-04)]' axes x2y1 w lines lw 3 lc rgbcolor '#00FF00',\
'nemo.exe.128tasks.chop1.clustered.codeblocks.fused.any.any.any.slope.csv' u ($4*FACTOR):(slope($5, strcol(3), strcol(1), $2)) ti 'Counter rate' axes x2y2 w lines lw 3 lc rgbcolor '#0000FF';

unset label;
unset arrow;

unset multiplot;
