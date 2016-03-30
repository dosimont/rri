X_LIMIT=128.29 # Do not touch this
FACTOR=1 # Do not touch this

set datafile separator ";";

# set term postscript eps solid color;
# set term pdfcairo solid color lw 2;
# set term png size 800,600;
# set term wxt size 800,600;

set multiplot title "Appl * Task * Thread * - Group_0 - Cluster_3"

##############################
## Routines part 
##############################

samplecls(ret,r,g,t) = (r eq 'Cluster_3' && g == 0  && t eq 'cl') ? ret : NaN;

set size 1,0.20;
set origin 0,0.75;

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

set size 1,0.73;
set origin 0,0;
set tmargin 0; set lmargin 14; set rmargin 17;

set key bottom outside center horizontal samplen 1;
set x2range [0:1];
set yrange [0:*];
set y2range [0:*];
#set x2tics nomirror format "%.02f";
set xlabel 'Time (ms)';
set xtics nomirror format "%.02f";
set xtics ( 0.0 , 1./5.*X_LIMIT, 2./5.*X_LIMIT, 3./5.*X_LIMIT, 4./5.*X_LIMIT, 5./5.*X_LIMIT, X_LIMIT/FACTOR);
set xrange [0:X_LIMIT*1./FACTOR];
set ylabel 'Counter ratio per instruction';
set y2label 'MIPS';
set ytics nomirror format "%g";
set y2tics nomirror format "%g";

# Breakpoints
# Unneeded phases separators, nb. breakpoints = 2

slope_PAPI_TOT_INS(ret,c,r,g) = (c eq 'PAPI_TOT_INS' && r eq 'Cluster_3' && g == 0 ) ? ret : NaN;

plot \
'nemo.exe.128tasks.chop1.clustered.codeblocks.fused.any.any.any.slope.csv' u ($4*FACTOR):(slope_PAPI_TOT_INS($5, strcol(3), strcol(1), $2)) ti 'MIPS' axes x2y2 w lines lw 3;

unset label;
unset arrow;

unset multiplot;
