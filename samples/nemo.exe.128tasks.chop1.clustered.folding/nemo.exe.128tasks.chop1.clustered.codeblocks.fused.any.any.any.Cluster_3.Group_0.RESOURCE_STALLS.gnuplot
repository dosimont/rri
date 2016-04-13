X_LIMIT=128.29 # Do not touch this
FACTOR=1 # Do not touch this

set datafile separator ";";

# set term postscript eps solid color;
# set term pdfcairo solid color lw 2;
# set term png size 800,600;
# set term wxt size 800,600;

set multiplot title "Appl * Task * Thread * - Group_0 - Cluster_3\nDuration = 128.29 ms, Counter = 311.31 Mevents";

##############################
## Routines part 
##############################

samplecls(ret,r,g,t) = (r eq 'Cluster_3' && g == 0  && t eq 'cl') ? ret : NaN;

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

set obj rect from graph 0.001*FACTOR, graph 0 to graph 0.080*FACTOR, graph 1 fs transparent solid 0.50 noborder fc rgbcolor '#006D01' behind # Routine: tra_nxt_fix 7.840%
set obj rect from graph 0.080*FACTOR, graph 0 to graph 0.113*FACTOR, graph 1 fs transparent solid 0.50 noborder fc rgbcolor '#B30200' behind # Routine: stp 3.336%
set obj rect from graph 0.115*FACTOR, graph 0 to graph 0.166*FACTOR, graph 1 fs transparent solid 0.50 noborder fc rgbcolor '#03A200' behind # Routine: dyn_keg 5.161%
set obj rect from graph 0.189*FACTOR, graph 0 to graph 0.273*FACTOR, graph 1 fs transparent solid 0.50 noborder fc rgbcolor '#AFAE29' behind # Routine: dyn_zad 8.375%
set obj rect from graph 0.285*FACTOR, graph 0 to graph 0.371*FACTOR, graph 1 fs transparent solid 0.50 noborder fc rgbcolor '#77C4FF' behind # Routine: vor_een 8.608%
set obj rect from graph 0.387*FACTOR, graph 0 to graph 0.449*FACTOR, graph 1 fs transparent solid 0.50 noborder fc rgbcolor '#0201FF' behind # Routine: dyn_ldf_lap 6.249%
set obj rect from graph 0.449*FACTOR, graph 0 to graph 0.586*FACTOR, graph 1 fs transparent solid 0.50 noborder fc rgbcolor '#B30200' behind # Routine: stp 13.658%
set obj rect from graph 0.586*FACTOR, graph 0 to graph 0.882*FACTOR, graph 1 fs transparent solid 0.50 noborder fc rgbcolor '#ED0100' behind # Routine: dyn_zdf_imp 29.660%
set obj rect from graph 0.882*FACTOR, graph 0 to graph 0.942*FACTOR, graph 1 fs transparent solid 0.50 noborder fc rgbcolor '#B30200' behind # Routine: stp 5.949%
set obj rect from graph 0.942*FACTOR, graph 0 to graph 1.000*FACTOR, graph 1 fs transparent solid 0.50 noborder fc rgbcolor '#AEAF29' behind # Routine: dyn_spg_flt 5.816%

# Summary for routine Unresolved 0.039%
# Summary for routine _start 0.060%
# Summary for routine dyn_adv 2.390%
# Summary for routine dyn_keg 5.161%
# Summary for routine dyn_ldf 0.008%
# Summary for routine dyn_ldf_lap 6.249%
# Summary for routine dyn_spg 0.008%
# Summary for routine dyn_spg_flt 5.816%
# Summary for routine dyn_vor 0.032%
# Summary for routine dyn_zad 8.375%
# Summary for routine dyn_zdf 0.004%
# Summary for routine dyn_zdf_imp 29.660%
# Summary for routine nemo 0.024%
# Summary for routine nemo_gcm 0.004%
# Summary for routine stp 25.723%
# Summary for routine tra_nxt_fix 7.840%
# Summary for routine vor_een 8.608%

set label center "nemo_gcm >\nstp >\ntra_nxt_fix\n[238]" at second 0.041*FACTOR, graph 0.5 rotate by 90 tc rgbcolor 'black' front
set label center "nemo >\nnemo_gcm >\nstp\n[242]" at second 0.097*FACTOR, graph 0.5 rotate by 90 tc rgbcolor 'black' front
set label center "stp >\ndyn_adv >\ndyn_keg\n[114]" at second 0.140*FACTOR, graph 0.5 rotate by 90 tc rgbcolor 'black' front
set label center "stp >\ndyn_adv >\ndyn_zad\n[140]" at second 0.231*FACTOR, graph 0.5 rotate by 90 tc rgbcolor 'black' front
set label center "stp >\ndyn_vor >\nvor_een\n[708]" at second 0.328*FACTOR, graph 0.5 rotate by 90 tc rgbcolor 'black' front
set label center "stp >\ndyn_ldf >\ndyn_ldf_lap\n[136]" at second 0.418*FACTOR, graph 0.5 rotate by 90 tc rgbcolor 'black' front
set label center "nemo >\nnemo_gcm >\nstp\n[242]" at second 0.517*FACTOR, graph 0.5 rotate by 90 tc rgbcolor 'black' front
set label center "stp >\ndyn_zdf >\ndyn_zdf_imp\n[236]" at second 0.734*FACTOR, graph 0.5 rotate by 90 tc rgbcolor 'black' front
set label center "nemo >\nnemo_gcm >\nstp\n[242]" at second 0.912*FACTOR, graph 0.5 rotate by 90 tc rgbcolor 'black' front
set label center "stp >\ndyn_spg >\ndyn_spg_flt\n[215]" at second 0.971*FACTOR, graph 0.5 rotate by 90 tc rgbcolor 'black' front

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
set ylabel 'Normalized RESOURCE_STALLS';
set xlabel 'Time (ms)';
set xtics nomirror format "%.02f";
set xtics ( 0.0 , 1./5.*X_LIMIT, 2./5.*X_LIMIT, 3./5.*X_LIMIT, 4./5.*X_LIMIT, 5./5.*X_LIMIT, X_LIMIT/FACTOR);
set xrange [0:X_LIMIT*1./FACTOR];
set y2label 'RESOURCE_STALLS rate (in Mevents/s)';

# Mean rate
set label "" at first X_LIMIT*1./FACTOR, second 2426.56 point pt 3 ps 2 lc rgbcolor "#707070";

# Breakpoints
# Unneeded phases separators, nb. breakpoints = 2

# Data accessors to CSV
sampleexcluded(ret,c,r,g,t) = (c eq 'RESOURCE_STALLS' && r eq 'Cluster_3' && g == 0  && t eq 'e') ? ret : NaN;
sampleunused(ret,c,r,g,t) = (c eq 'RESOURCE_STALLS' && r eq 'Cluster_3' && g ==  0 && t eq 'un') ? ret : NaN;
sampleused(ret,c,r,g,t) = (c eq 'RESOURCE_STALLS' && r eq 'Cluster_3' && g == 0 && t eq 'u') ? ret : NaN;
interpolation(ret,c,r,g) = (c eq 'RESOURCE_STALLS' && r eq 'Cluster_3' && g == 0 ) ? ret : NaN;
slope(ret,c,r,g) = (c eq 'RESOURCE_STALLS' && r eq 'Cluster_3' && g == 0 ) ? ret : NaN;

# Plot command
plot \
NaN ti 'Mean RESOURCE_STALLS rate' w points pt 3 lc rgbcolor "#707070" ,\
'nemo.exe.128tasks.chop1.clustered.codeblocks.fused.any.any.any.dump.csv' u ($4*FACTOR):(sampleexcluded($6, strcol(5), strcol(2), $3, strcol(1))) ti 'Excluded samples (965)' axes x2y1 w points pt 3 lc rgbcolor '#A0A0A0',\
'nemo.exe.128tasks.chop1.clustered.codeblocks.fused.any.any.any.dump.csv' u ($4*FACTOR):(sampleunused($6, strcol(5), strcol(2), $3, strcol(1))) ti 'Unused samples (1907)' axes x2y1 w points pt 3 lc rgbcolor '#FFA0A0',\
'nemo.exe.128tasks.chop1.clustered.codeblocks.fused.any.any.any.dump.csv' u ($4*FACTOR):(sampleused($6, strcol(5), strcol(2), $3, strcol(1))) ti 'Used samples (1500)' axes x2y1 w points pt 3 lc rgbcolor '#FF0000',\
'nemo.exe.128tasks.chop1.clustered.codeblocks.fused.any.any.any.interpolate.csv' u ($4*FACTOR):(interpolation($5, strcol(3), strcol(1), $2)) ti 'Fitting [Kriger (nuget=1.0e-04)]' axes x2y1 w lines lw 3 lc rgbcolor '#00FF00',\
'nemo.exe.128tasks.chop1.clustered.codeblocks.fused.any.any.any.slope.csv' u ($4*FACTOR):(slope($5, strcol(3), strcol(1), $2)) ti 'Counter rate' axes x2y2 w lines lw 3 lc rgbcolor '#0000FF';

unset label;
unset arrow;

unset multiplot;
