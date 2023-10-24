
%-- zad 1

a = 4 - 6j;
b = -2 + 3j;

sum = a + b;
diff = a - b;
prod = a .* b;
frac = a ./ b;

[r, theta] = algToExpForm(sum);

function [r, theta] = algToExpForm(z)
    r = abs(z);
    theta = rad2deg(angle(z));
end



kMaxLinSpace = 20;
kLinSpaceStep = 0.1;
linspace = 0:kLinSpaceStep:kMaxLinSpace;

figure();

hold on;
plot(linspace, expSin(linspace, 2, 3), '-w');
plot(linspace, expSin(linspace, 1, -3), ':b');
hold off;


function expSin = expSin(x,a,b)
    expSin = a * exp(b .* sin(x));
end

kMinLinSpace = -3;
kMaxLinSpace = 3;
kLinSpaceStep = 0.1;
linspace = kMinLinSpace:kLinSpaceStep:kMaxLinSpace;

foo();

function result = foo()
    [x, y] = meshgrid(-3:0.1:3);
    z = exp(-(x-1).^2 - y.^2) - exp(-(x+1).^2 - y.^2);
    surf(x, y, z);
end


%-- e^(2sin(pi))
res1 = exp(2*sin(pi));

%-- cos(pi/3)^6
res2 = cos(pi / )

%{
    Zdefiniować macierz 𝑪 = [...] i wykonać poniższe polecenia:
    * Przypisać do zmiennej y wartość 𝑪𝟑,𝟐
    * Nadać elementowi 𝑪𝟒,𝟐wartość 7.
    * Wyciąć z macierzy C jej trzeci wiersz i przypisać do zmiennej d.
    * Wyciąć z macierzy C drugą i czwartą kolumnę i przypisać je do zmiennej D.
    * Wyciąć fragment macierzy C, zwierający wiersze od 2. do 3. i kolumny od 2.
        do 4. Wynik przypisać do zmiennej E.
%}


C = [
        2,0,1,4,7;
        3,9,8,5,6;
        1,5,0,4,3;
]

y = C(3,2);
C(4,2) = 7;

d = C(3,:)
D = C(:, 2:4)
E = C(2:3, 2:4)
size(C)






F = zeros(3,5);

for i = 1:3
    for j = 1:5
        F(i,j) = formula(i,j)
    end
end


function output = formula(i,j)
    if j == 0 
        output = NaN
    else
        output = sqrt(1 + i ./ j)
    end
end

%{
    Zdefiniować macierze A i B postaci: 𝑨 = [1 0; 3 2], 𝑩 = [1 2; 3 4]. Wykonać poniższe polecenia:
        * Obliczyć iloczyny 𝑨 ∙ 𝑩 oraz 𝑩 ∙ 𝑨 w sposób macierzowy i tablicowy.
        * Obliczyć 𝑨3 w sposób macierzowy i tablicowy
        * Wyznaczyć macierz 𝑪 = (𝑨 + 𝑩𝑇)/2
%}


A = [
    1,0;
    3,2;
]

B = [
    1,2;
    3,4;
]


matrixProductAB = A * B
matrixProductAB_ = matrixMultiplication(A,B);
matrixProductBA = B * A;

matrixAAA = A ^ 3;
matrixAAA = matrixMultiplication(matrixMultiplication(A, A), A);

C = (A + B') / 2


function result = matrixMultiplication(A,B)
    
    rowCount = size(A);
    colCount = size(B);
    result = zeros(rowCount(1), colCount(2));

    for i = 1:rowCount(1)
        for j = 1:colCount(2)
            result(i,j) = A(i,:) * B(:,j);
        end 
    end
end

system = [
    3,2,-1;
    4,2,-1;
    -2,-1,1;
];

results = [1;2;3];

% [A,B] = equationsToMatrix(system, results)

solution = system \ results;

someVector = rand(1,10);
computeVariance(someVector)
var(someVector)



function variance = computeVariance(inputVector)
    meanValue = mean(inputVector);
    varianceSum = 0;

    for i = 1:length(inputVector)
        varianceSum = varianceSum + (meanValue - inputVector(i)) .^ 2;
    end
    variance = varianceSum ./ length(inputVector);
end

factorial(5)

function result = factorial(input)
    if input < 2
        result = 1;
    else
        result = input * factorial(input - 1);
    end
end

% Define the range of x values
x = -2*pi:0.01:2*pi;

% Initialize the number of terms in the Taylor series
n_values = [1, 3, 5, 10, 30, 100];

% Initialize the result vector
result = zeros(length(x), length(n_values));

% Calculate the Taylor series approximation for each value of n
for j = 1:length(n_values)
    n = n_values(j);
    term = zeros(size(x));
    
    for k = 0:n
        term = term + ((-1)^k * x.^(2*k + 1)) / factorial(2*k + 1);
    end
    
    result(:, j) = term;
end

% Plot the results
figure;
hold on;

for j = 1:length(n_values)
    plot(x, result(:, j), 'DisplayName', sprintf('n = %d', n_values(j)));
end

% Plot the sin(x) function for comparison
plot(x, sin(x), 'k--', 'DisplayName', 'sin(x)');
legend;
title('Taylor Series Approximation of sin(x)');
xlabel('x');
ylabel('Approximation');
grid on;

hold off;
