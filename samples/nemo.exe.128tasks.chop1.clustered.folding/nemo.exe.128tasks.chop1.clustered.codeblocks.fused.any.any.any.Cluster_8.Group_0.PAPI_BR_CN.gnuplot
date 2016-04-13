X_LIMIT=128.28 # Do not touch this
FACTOR=1 # Do not touch this

set datafile separator ";";

# set term postscript eps solid color;
# set term pdfcairo solid color lw 2;
# set term png size 800,600;
# set term wxt size 800,600;

set multiplot title "Appl * Task * Thread * - Group_0 - Cluster_8\nDuration = 128.28 ms, Counter = 7.15 Mevents";

##############################
## Routines part 
##############################

samplecls(ret,r,g,t) = (r eq 'Cluster_8' && g == 0  && t eq 'cl') ? ret : NaN;

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

set obj rect from graph 0.015*FACTOR, graph 0 to graph 0.096*FACTOR, graph 1 fs transparent solid 0.50 noborder fc rgbcolor '#006D01' behind # Routine: tra_nxt_fix 8.056%
set obj rect from graph 0.096*FACTOR, graph 0 to graph 0.129*FACTOR, graph 1 fs transparent solid 0.50 noborder fc rgbcolor '#B30200' behind # Routine: stp 3.343%
set obj rect from graph 0.129*FACTOR, graph 0 to graph 0.181*FACTOR, graph 1 fs transparent solid 0.50 noborder fc rgbcolor '#03A200' behind # Routine: dyn_keg 5.201%
set obj rect from graph 0.187*FACTOR, graph 0 to graph 0.295*FACTOR, graph 1 fs transparent solid 0.50 noborder fc rgbcolor '#AFAE29' behind # Routine: dyn_zad 10.878%
set obj rect from graph 0.314*FACTOR, graph 0 to graph 0.392*FACTOR, graph 1 fs transparent solid 0.50 noborder fc rgbcolor '#77C4FF' behind # Routine: vor_een 7.733%
set obj rect from graph 0.407*FACTOR, graph 0 to graph 0.470*FACTOR, graph 1 fs transparent solid 0.50 noborder fc rgbcolor '#0201FF' behind # Routine: dyn_ldf_lap 6.237%
set obj rect from graph 0.486*FACTOR, graph 0 to graph 0.549*FACTOR, graph 1 fs transparent solid 0.50 noborder fc rgbcolor '#0101AE' behind # Routine: hpg_zps 6.341%
set obj rect from graph 0.565*FACTOR, graph 0 to graph 0.895*FACTOR, graph 1 fs transparent solid 0.50 noborder fc rgbcolor '#ED0100' behind # Routine: dyn_zdf_imp 32.997%
set obj rect from graph 0.895*FACTOR, graph 0 to graph 0.932*FACTOR, graph 1 fs transparent solid 0.50 noborder fc rgbcolor '#B30200' behind # Routine: stp 3.781%
set obj rect from graph 0.934*FACTOR, graph 0 to graph 1.000*FACTOR, graph 1 fs transparent solid 0.50 noborder fc rgbcolor '#AEAF29' behind # Routine: dyn_spg_flt 6.645%

# Summary for routine dyn_adv 0.533%
# Summary for routine dyn_hpg 0.047%
# Summary for routine dyn_keg 5.201%
# Summary for routine dyn_ldf 0.032%
# Summary for routine dyn_ldf_lap 6.237%
# Summary for routine dyn_spg 0.120%
# Summary for routine dyn_spg_flt 6.645%
# Summary for routine dyn_vor 0.056%
# Summary for routine dyn_zad 10.878%
# Summary for routine dyn_zdf 0.033%
# Summary for routine dyn_zdf_imp 32.997%
# Summary for routine hpg_zps 6.341%
# Summary for routine nemo 0.045%
# Summary for routine nemo_gcm 0.001%
# Summary for routine stp 15.045%
# Summary for routine tra_nxt_fix 8.056%
# Summary for routine vor_een 7.733%

set label center "nemo_gcm >\nstp >\ntra_nxt_fix\n[240]" at second 0.056*FACTOR, graph 0.5 rotate by 90 tc rgbcolor 'black' front
set label center "nemo >\nnemo_gcm >\nstp\n[242]" at second 0.113*FACTOR, graph 0.5 rotate by 90 tc rgbcolor 'black' front
set label center "stp >\ndyn_adv >\ndyn_keg\n[99]" at second 0.155*FACTOR, graph 0.5 rotate by 90 tc rgbcolor 'black' front
set label center "stp >\ndyn_adv >\ndyn_zad\n[140]" at second 0.241*FACTOR, graph 0.5 rotate by 90 tc rgbcolor 'black' front
set label center "stp >\ndyn_vor >\nvor_een\n[708]" at second 0.353*FACTOR, graph 0.5 rotate by 90 tc rgbcolor 'black' front
set label center "stp >\ndyn_ldf >\ndyn_ldf_lap\n[136]" at second 0.438*FACTOR, graph 0.5 rotate by 90 tc rgbcolor 'black' front
set label center "stp >\ndyn_hpg >\nhpg_zps\n[326]" at second 0.517*FACTOR, graph 0.5 rotate by 90 tc rgbcolor 'black' front
set label center "stp >\ndyn_zdf >\ndyn_zdf_imp\n[150]" at second 0.730*FACTOR, graph 0.5 rotate by 90 tc rgbcolor 'black' front
set label center "nemo >\nnemo_gcm >\nstp\n[242]" at second 0.913*FACTOR, graph 0.5 rotate by 90 tc rgbcolor 'black' front
set label center "stp >\ndyn_spg >\ndyn_spg_flt\n[215]" at second 0.967*FACTOR, graph 0.5 rotate by 90 tc rgbcolor 'black' front

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
set ylabel 'Normalized PAPI_BR_CN';
set xlabel 'Time (ms)';
set xtics nomirror format "%.02f";
set xtics ( 0.0 , 1./5.*X_LIMIT, 2./5.*X_LIMIT, 3./5.*X_LIMIT, 4./5.*X_LIMIT, 5./5.*X_LIMIT, X_LIMIT/FACTOR);
set xrange [0:X_LIMIT*1./FACTOR];
set y2label 'PAPI_BR_CN rate (in Mevents/s)';

# Mean rate
set label "" at first X_LIMIT*1./FACTOR, second 55.72 point pt 3 ps 2 lc rgbcolor "#707070";

# Breakpoints
# Unneeded phases separators, nb. breakpoints = 2

# Data accessors to CSV
sampleexcluded(ret,c,r,g,t) = (c eq 'PAPI_BR_CN' && r eq 'Cluster_8' && g == 0  && t eq 'e') ? ret : NaN;
sampleunused(ret,c,r,g,t) = (c eq 'PAPI_BR_CN' && r eq 'Cluster_8' && g ==  0 && t eq 'un') ? ret : NaN;
sampleused(ret,c,r,g,t) = (c eq 'PAPI_BR_CN' && r eq 'Cluster_8' && g == 0 && t eq 'u') ? ret : NaN;
interpolation(ret,c,r,g) = (c eq 'PAPI_BR_CN' && r eq 'Cluster_8' && g == 0 ) ? ret : NaN;
slope(ret,c,r,g) = (c eq 'PAPI_BR_CN' && r eq 'Cluster_8' && g == 0 ) ? ret : NaN;

# Plot command
plot \
NaN ti 'Mean PAPI_BR_CN rate' w points pt 3 lc rgbcolor "#707070" ,\
'nemo.exe.128tasks.chop1.clustered.codeblocks.fused.any.any.any.dump.csv' u ($4*FACTOR):(sampleexcluded($6, strcol(5), strcol(2), $3, strcol(1))) ti 'Excluded samples (192)' axes x2y1 w points pt 3 lc rgbcolor '#A0A0A0',\
'nemo.exe.128tasks.chop1.clustered.codeblocks.fused.any.any.any.dump.csv' u ($4*FACTOR):(sampleused($6, strcol(5), strcol(2), $3, strcol(1))) ti 'Used samples (550)' axes x2y1 w points pt 3 lc rgbcolor '#FF0000',\
'nemo.exe.128tasks.chop1.clustered.codeblocks.fused.any.any.any.interpolate.csv' u ($4*FACTOR):(interpolation($5, strcol(3), strcol(1), $2)) ti 'Fitting [Kriger (nuget=1.0e-04)]' axes x2y1 w lines lw 3 lc rgbcolor '#00FF00',\
'nemo.exe.128tasks.chop1.clustered.codeblocks.fused.any.any.any.slope.csv' u ($4*FACTOR):(slope($5, strcol(3), strcol(1), $2)) ti 'Counter rate' axes x2y2 w lines lw 3 lc rgbcolor '#0000FF';

unset label;
unset arrow;

unset multiplot;
