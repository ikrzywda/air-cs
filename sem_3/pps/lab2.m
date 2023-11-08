SAMPLING_FREQUENCY = 200;
SAMPLE_COUNT = 1000;

% zadanie 1
t1 = createSingalTimeVec(SAMPLING_FREQUENCY, SAMPLE_COUNT);

sine1 = createSineSignal( ...
    t1, 2, 10, 0, 0);

sine2 = createSineSignal( ...
    t1, 6, 20, 0, 0);

sine3 = createSineSignal( ...
    t1, 4, 15, 0, 0);

sine3 = cropSignal(1,3,SAMPLING_FREQUENCY,SAMPLE_COUNT,sine3);

figure();
subplot(3,1,1);
plot(t1, sine1 + sine2);
subplot(3,1,2);
plot(t1, sine1 + sine2 + sine3);

% zadanie 2
randomNoise1 = createRandomNoiseValueRange(t1, @rand, 0, 1);
randomNoise2 = createRandomNoiseValueRange(t1, @rand, 0.01, 0.05);
randomNoiseNormal1 = createRandomNoiseValueRange(t1, @randn, 0, 1);
randomNoiseNormal2 = createRandomNoiseMeanValue(t1, @randn, 0.01, 0.5);
plotSigWithNoise(t1, randomNoiseNormal2, sine1);


% zadanie 3
t2 = createSingalTimeVec(200, 2000);
figure();
subplot(3,1,1);
plot(t2, chirp(t2, 1, 5, 5));
subplot(3,1,2);
plot(t2, chirp(t2, 1, 5, 2));
subplot(3,1,3);
plot(t2, chirp(t2, 1, 5, 5, "logarithmic"));


function plotSigWithNoise(timeVec, noise, sig)
    figure();
    subplot(3,1,1);
    plot(timeVec, sig);
    subplot(3,1,2);
    plot(timeVec, noise);
    subplot(3,1,3);
    plot(timeVec, noise + sig);
end

function t = createSingalTimeVec(...
    samplingFrequency, sampleCount)
    step = 1 / samplingFrequency;
    maxTime = (sampleCount - 1) / samplingFrequency;
    t = 0 : step : maxTime;
end

function sig = createSineSignal( ...
    timeVec, amplitude, frequency, phaseShift, ...
    constantTerm)

    sig = constantTerm + amplitude * sin(2 * pi * frequency * timeVec + phaseShift);
end

function croppedSignal = cropSignal(...
    sigStartSec, sigEndSec, samplingFrequency, sampleCount, signal)
    startIndex = round(sigStartSec * samplingFrequency); 
    endIndex = round(sigEndSec * samplingFrequency); 

    startIndex = max(1, min(startIndex, sampleCount));
    endIndex = max(1, min(endIndex, sampleCount));

    maskingVector = [zeros(1, startIndex - 1), ones(1, endIndex - startIndex + 1), ...
        zeros(1, sampleCount - endIndex)];
    croppedSignal = signal .* maskingVector;
end

function sig = createRandomNoiseValueRange( ...
    timeVec, randFunction, minVal, maxVal)
    scalingFactor = maxVal - minVal;
    sig = randFunction(1, length(timeVec));
    sig = sig .* scalingFactor;
    sig = sig + minVal;
end

function sig = createRandomNoiseMeanValue( ...
    timeVec, randFunction, mean, variance)
    sig = mean + sqrt(variance) .* randFunction(1, length(timeVec));
end
