% Igor Krzywda, 275480
% gr. 5, piatek, 11:15
% cw. 1

clear;
clc;

aN = 0.25;
TwewN = 20;
TzewN = -20;
TpN = 10;
QgN = 5000;

KcwN = computeKcw(QgN, TwewN, TzewN,TpN, aN);
KcpN = computeKcp(QgN, TwewN, TzewN,TpN, aN);
Tp = computeTp(QgN, TzewN, KcwN, KcpN, aN);
Twew = computeTwew(QgN, TzewN, KcwN, KcpN, aN);

qMin = 0;
qMax = 5000;

TzewMin = TzewN;
TzewMax = 20;

qVals = [qMin:1000:qMax];
TzewVals = [TzewMin:10:TzewMax];

% T_p(T_zew)
f1 = figure;
tpFromTzewFig = figure(1);
hold on
for q = qVals
    plot(TzewVals, computeTp(q, TzewVals, KcwN, KcpN, aN), '-');
end
plot(TzewN, TpN, 'o');
hold off

% T_p(Q_g)
f2 = figure;
hold on
for t = TzewVals
    plot(qVals, computeTp(qVals, t, KcwN, KcpN, aN), '-');
end
plot(QgN, TpN, 'o');
hold off


function Kcw = computeKcw(q, twew, tzew, tp, a)
    denominator = (twew - tzew - a * (twew - tp));
    Kcw = q / denominator;
end

function Kcp = computeKcp(q, twew, tzew, tp, a)
    denominator = (twew - tzew - a * (twew - tp)) * (tp - tzew);
    Kcp = (a * q * (twew - tp)) / denominator;
end


function Tp = computeTp(q, tzew, kcw, kcp, a)
    tempADenominator = a * kcw + kcp - (((a ^ 2) * kcw) / (1 + a));
    tempA = 1 / tempADenominator;
    tempBNominator = a * q + kcw * tzew;
    tempB = (tempBNominator / (1 + a)) - tzew;
    Tp = tempA * tempB;
end


function Twew = computeTwew(q, tzew, kcw, kcp, a)
    tempA = (q + kcw * tzew) / (kcw * (1 + a));
    tempB = 1 / (a * kcw + kcp);
    tempC = ((a * q + kcw * tzew) / (1 + a) - tzew);
    
    Twew = tempA - (a * kcw * (tempB - tempC));
end

    