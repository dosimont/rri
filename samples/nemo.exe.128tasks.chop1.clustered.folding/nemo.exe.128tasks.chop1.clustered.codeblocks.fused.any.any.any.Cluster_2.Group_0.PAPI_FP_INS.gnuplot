X_LIMIT=101.17 # Do not touch this
FACTOR=1 # Do not touch this

set datafile separator ";";

# set term postscript eps solid color;
# set term pdfcairo solid color lw 2;
# set term png size 800,600;
# set term wxt size 800,600;

set multiplot title "Appl * Task * Thread * - Group_0 - Cluster_2\nDuration = 101.17 ms, Counter = 25.32 Mevents";

##############################
## Routines part 
##############################

samplecls(ret,r,g,t) = (r eq 'Cluster_2' && g == 0  && t eq 'cl') ? ret : NaN;

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

set obj rect from graph 0.000*FACTOR, graph 0 to graph 0.139*FACTOR, graph 1 fs transparent solid 0.50 noborder fc rgbcolor '#747575' behind # Routine: ssh_wzv 13.914%
set obj rect from graph 0.139*FACTOR, graph 0 to graph 0.167*FACTOR, graph 1 fs transparent solid 0.50 noborder fc rgbcolor '#B30200' behind # Routine: stp 2.768%
set obj rect from graph 0.167*FACTOR, graph 0 to graph 0.303*FACTOR, graph 1 fs transparent solid 0.50 noborder fc rgbcolor '#FF2F01' behind # Routine: eos_bn2 13.603%
set obj rect from graph 0.303*FACTOR, graph 0 to graph 0.336*FACTOR, graph 1 fs transparent solid 0.50 noborder fc rgbcolor '#B30200' behind # Routine: stp 3.318%
set obj rect from graph 0.336*FACTOR, graph 0 to graph 0.437*FACTOR, graph 1 fs transparent solid 0.50 noborder fc rgbcolor '#696A01' behind # Routine: zdf_tke 10.061%
set obj rect from graph 0.437*FACTOR, graph 0 to graph 1.000*FACTOR, graph 1 fs transparent solid 0.50 noborder fc rgbcolor '#000171' behind # Routine: tke_tke 56.318%

# Summary for routine eos_bn2 13.603%
# Summary for routine nemo 0.011%
# Summary for routine nemo_gcm 0.002%
# Summary for routine ssh_wzv 13.914%
# Summary for routine stp 6.091%
# Summary for routine tke_tke 56.318%
# Summary for routine zdf_tke 10.061%

set label center "nemo_gcm >\nstp >\nssh_wzv\n[245]" at second 0.070*FACTOR, graph 0.5 rotate by 90 tc rgbcolor 'black' front
set label center "nemo >\nnemo_gcm >\nstp\n[140]" at second 0.153*FACTOR, graph 0.5 rotate by 90 tc rgbcolor 'black' front
set label center "nemo_gcm >\nstp >\neos_bn2\n[594]" at second 0.235*FACTOR, graph 0.5 rotate by 90 tc rgbcolor 'black' front
set label center "nemo >\nnemo_gcm >\nstp\n[140]" at second 0.320*FACTOR, graph 0.5 rotate by 90 tc rgbcolor 'black' front
set label center "nemo_gcm >\nstp >\nzdf_tke\n[209]" at second 0.387*FACTOR, graph 0.5 rotate by 90 tc rgbcolor 'black' front
set label center "stp >\nzdf_tke >\ntke_tke\n[436]" at second 0.718*FACTOR, graph 0.5 rotate by 90 tc rgbcolor 'black' front

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
set ylabel 'Normalized PAPI_FP_INS';
set xlabel 'Time (ms)';
set xtics nomirror format "%.02f";
set xtics ( 0.0 , 1./5.*X_LIMIT, 2./5.*X_LIMIT, 3./5.*X_LIMIT, 4./5.*X_LIMIT, 5./5.*X_LIMIT, X_LIMIT/FACTOR);
set xrange [0:X_LIMIT*1./FACTOR];
set y2label 'PAPI_FP_INS rate (in Mevents/s)';

# Mean rate
set label "" at first X_LIMIT*1./FACTOR, second 250.32 point pt 3 ps 2 lc rgbcolor "#707070";

# Breakpoints
# Unneeded phases separators, nb. breakpoints = 2

# Data accessors to CSV
sampleexcluded(ret,c,r,g,t) = (c eq 'PAPI_FP_INS' && r eq 'Cluster_2' && g == 0  && t eq 'e') ? ret : NaN;
sampleunused(ret,c,r,g,t) = (c eq 'PAPI_FP_INS' && r eq 'Cluster_2' && g ==  0 && t eq 'un') ? ret : NaN;
sampleused(ret,c,r,g,t) = (c eq 'PAPI_FP_INS' && r eq 'Cluster_2' && g == 0 && t eq 'u') ? ret : NaN;
interpolation(ret,c,r,g) = (c eq 'PAPI_FP_INS' && r eq 'Cluster_2' && g == 0 ) ? ret : NaN;
slope(ret,c,r,g) = (c eq 'PAPI_FP_INS' && r eq 'Cluster_2' && g == 0 ) ? ret : NaN;

# Plot command
plot \
NaN ti 'Mean PAPI_FP_INS rate' w points pt 3 lc rgbcolor "#707070" ,\
'nemo.exe.128tasks.chop1.clustered.codeblocks.fused.any.any.any.dump.csv' u ($4*FACTOR):(sampleexcluded($6, strcol(5), strcol(2), $3, strcol(1))) ti 'Excluded samples (1605)' axes x2y1 w points pt 3 lc rgbcolor '#A0A0A0',\
'nemo.exe.128tasks.chop1.clustered.codeblocks.fused.any.any.any.dump.csv' u ($4*FACTOR):(sampleunused($6, strcol(5), strcol(2), $3, strcol(1))) ti 'Unused samples (1599)' axes x2y1 w points pt 3 lc rgbcolor '#FFA0A0',\
'nemo.exe.128tasks.chop1.clustered.codeblocks.fused.any.any.any.dump.csv' u ($4*FACTOR):(sampleused($6, strcol(5), strcol(2), $3, strcol(1))) ti 'Used samples (1500)' axes x2y1 w points pt 3 lc rgbcolor '#FF0000',\
'nemo.exe.128tasks.chop1.clustered.codeblocks.fused.any.any.any.interpolate.csv' u ($4*FACTOR):(interpolation($5, strcol(3), strcol(1), $2)) ti 'Fitting [Kriger (nuget=1.0e-04)]' axes x2y1 w lines lw 3 lc rgbcolor '#00FF00',\
'nemo.exe.128tasks.chop1.clustered.codeblocks.fused.any.any.any.slope.csv' u ($4*FACTOR):(slope($5, strcol(3), strcol(1), $2)) ti 'Counter rate' axes x2y2 w lines lw 3 lc rgbcolor '#0000FF';

unset label;
unset arrow;

unset multiplot;
