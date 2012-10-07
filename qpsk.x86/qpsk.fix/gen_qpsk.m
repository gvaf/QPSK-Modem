% Generate QPSK header file (Fixed point Version)

function gen_qpsk()

MESSAGE_LENGTH  = 3;      % Length of sound in seconds
AUDIO_FS        = 8000;   % Audio frequency in Hz  
CARRIER_FREQ    = 1000;   %Carrier frequency in Hz  
SYMBOL_FREQ     = 500;    % Symbol frequency in Hz  
CUT_OFF_FREQ    = 500;    % Filter cut off frequency 
NUM_TAPS        = 40;     % Number of Filter's TAPS
BUFFER_SIZE     = 1000;   % The size of the buffer 
HEADER_C        = 'qpsk.h'; 

% Generate carriers
Icarrier = cos ( 2 * pi * CARRIER_FREQ * (0 : (AUDIO_FS/CARRIER_FREQ - 1)) / AUDIO_FS );
Qcarrier = sin ( 2 * pi * CARRIER_FREQ * (0 : (AUDIO_FS/CARRIER_FREQ - 1)) / AUDIO_FS );

% Generate RRC filter and filter I and Q
b = firrcos(NUM_TAPS, CUT_OFF_FREQ, .3, AUDIO_FS, 'rolloff', 'sqrt');

fid = fopen(HEADER_C, 'wt');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

fprintf(fid, '/** QPSK Modulation Parameters\n\t!!! Automatically Generated from gen_qpsk.m matlab file !!!\n**/');
fprintf(fid, '\n\n');

fprintf(fid, '#ifndef QPSK_PARAMETERS_H\n');
fprintf(fid, '#define QPSK_PARAMETERS_H\n\n');

fprintf(fid, '#define MESSAGE_LENGTH  %d      /* Length of sound in seconds */\n', MESSAGE_LENGTH);
fprintf(fid, '#define AUDIO_FS        %d   /* Audio frequency in Hz  */\n', AUDIO_FS);
fprintf(fid, '#define CARRIER_FREQ    %d   /* Carrier frequency in Hz  */\n', CARRIER_FREQ);
fprintf(fid, '#define SYMBOL_FREQ     %d    /* Symbol frequency in Hz  */\n', SYMBOL_FREQ);
fprintf(fid, '#define CUT_OFF_FREQ    %d    /* Filter cut off frequency */\n', CUT_OFF_FREQ); 
fprintf(fid, '#define NUM_TAPS        %d     /* Number of Filter TAPS */\n', NUM_TAPS);
fprintf(fid, '#define BUFFER_SIZE     %d   /* The size of the buffer */\n', BUFFER_SIZE);
fprintf(fid, '#define CARRIER_SIZE    %d   /* The size of the carrier for each period*/\n', size(Icarrier, 2) );
fprintf(fid, '#define HALF_BUFF_SIZE  %d   /* Half of the message buffer*/\n', (BUFFER_SIZE/2) );
fprintf(fid, '#define NUM_SAMPLES     %d   /* The number of samples*/\n', (AUDIO_FS / SYMBOL_FREQ) );
fprintf(fid, '#define SAMPLE_RANGE    %d   /* The size of modulated signal*/\n', (AUDIO_FS / SYMBOL_FREQ) * (BUFFER_SIZE/2) ); 
fprintf(fid, '\n');
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
fprintf(fid, '/* The In-phase channel */\n%s\n', 'const short Icarrier[] = {');

fprintf(fid, '\t%d',  toQ15(Icarrier(1)));
for j = 2:size(Icarrier, 2)
  fprintf(fid, ',\n\t %d',  toQ15(Icarrier(j)));
end


fprintf(fid, '\n};\n');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

fprintf(fid, '\n');

fprintf(fid, '/* The Quadrature Channel */\n%s\n', 'const short Qcarrier[] = {');

fprintf(fid, '\t%d',  toQ15(Qcarrier(1)));
for j = 2:size(Qcarrier, 2)
  fprintf(fid, ',\n\t%d',  toQ15(Qcarrier(j)));
end

fprintf(fid, '\n};\n');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

fprintf(fid, '\n');

fprintf(fid, '/* The RRC filter coefficients */\n%s\n', 'const short bcoeff[] = {');

fprintf(fid, '\t%d',  toQ15(b(1)));
for j = 2:size(b, 2)
  fprintf(fid, ',\n\t%d',  toQ15(b(j)));
end

fprintf(fid, '\n};\n');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
fprintf(fid, '\n#endif\n');

fclose(fid);
end

