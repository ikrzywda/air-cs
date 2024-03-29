DATA_PATH = "poland-temperature-data-2022.csv";
MONTH_INDEXING_ARRAY = 1:24;
MONTH_DATES_ARRAY = [getDatetimeMonthArrayForYear(YEAR) getDatetimeMonthArrayForYear(2021)];
TARGET_YEARS = [2021, 2022];
MONTH_LABELS = arrayfun(@(year, index) datestr(datenum(year, index, 1), 'mmmm yyyy'), ...
    repmat(TARGET_YEARS, 1, numel(MONTH_INDEXING_ARRAY)), ...
    repmat(MONTH_INDEXING_ARRAY, 1, numel(target_years)), ...
    'UniformOutput', false);cla

% Data input & sanitization
data_table = readtable(DATA_PATH);
data_table.temperature = fillmissing(data_table.temperature, 'linear');
assert(~any(isnan(data_table.temperature)), 'Assertion failed: Temperature contains NaN values.');



data_table_sliced_by_month = arrayfun( ...
    @(month) getMonthSlice(data_table, month), MONTH_DATES_ARRAY, 'uniformOutput', false ...
);

mean_yearly_temperature = mean(data_table.temperature);
mean_temperature_by_month_array = cellfun( ...
    @(month) mean(month.temperature), ...
    data_table_sliced_by_month ...
);

mean_temperature_by_day_array = cell2mat(arrayfun( ...
    @(day) mean(data_table.temperature((day * 4):(day + 1) * 4)), ...
    1:365, 'UniformOutput', false ...
));

std_by_month = cellfun( ...
    @(month_table) std(month_table.temperature), ...
    data_table_sliced_by_month ...
);

% Standarization for mean monthly temperatures
standardized_temperature_by_month = (mean_temperature_by_month_array - mean(mean_temperature_by_month_array)) ./ std(mean_temperature_by_month_array);
autocorr_result = xcorr(standardized_temperature_by_month);
xcov(autocorr_result);

figure;
hold on;
scatter(1:length(autocorr_result), autocorr_result, 'Marker', 'o', 'MarkerFaceColor', 'b', 'MarkerEdgeColor', 'b', 'DisplayName', 'Points');

for i = 1:length(autocorr_result)
    plot([i, i], [0, autocorr_result(i)], '--', 'Color', [0.5, 0.5, 0.5]);
end

title('Autocorrelation');
xlabel('lag');
grid on;
hold off;
saveas(gcf, "figures/autocorrelation-plot.png", "png");


% Plotting average monthly temperature
figure;
hold on;
plot(MONTH_INDEXING_ARRAY, mean_temperature_by_month_array);
plot(MONTH_INDEXING_ARRAY, mean_temperature_by_month_array, 'o');
errorbar(MONTH_INDEXING_ARRAY, mean_temperature_by_month_array, std_by_month);
xticks(MONTH_INDEXING_ARRAY);
xticklabels(MONTH_LABELS);
ylabel('Avg. temperature [C]')
hold off;
saveas(gcf, "figures/mean-monthly-temperature-plot.png", "png");

% Histogram for temperature with per-measurement data
figure();
histogram(data_table.temperature);
xlabel("Temperature[C]");
saveas(gcf, "figures/temperature-histogram.png", "png");

% Histogram for mean daily temperature data
bins = min(mean_temperature_by_day_array):2:max(mean_temperature_by_day_array);
figure();
% histogram(mean_temperature_by_day_array, 'BinEdges', bins);
histogram(mean_temperature_by_day_array);
saveas(gcf, "figures/temperature-by-day-histogram.png", "png");

function month_slice = getMonthSlice(data_table, target_month)
    if ~isa(data_table.date, 'datetime')
        data_table.date = datetime(data_table.date, 'InputFormat', 'yyyy-MM-dd HH:mm:ss');
    end

    target_month_year = [month(target_month), year(target_month)];
    month_slice = data_table( ...
        month(data_table.date) == target_month_year(1) ...
        & year(data_table.date) == target_month_year(2), ...
    :);
end

function month_slices = getMonthSlices(data_table)
    if ~isa(data_table.date, 'datetime')
        data_table.date = datetime(data_table.date, 'InputFormat', 'yyyy-MM-dd HH:mm:ss');
    end

    unique_months = unique(month(data_table.date));
    month_slices = cell(numel(unique_months), 1);

    for i = 1:numel(unique_months)
        target_month = unique_months(i);
        target_month_year = [target_month, year(data_table.date(1))];
        month_slices{i} = data_table( ...
            month(data_table.date) == target_month_year(1) ...
            & year(data_table.date) == target_month_year(2), ...
        :);
    end
end


function month_dates_array = getDatetimeMonthArrayForYear(year)
    month_dates_array = arrayfun( ...
    @(month_index) ...
        datetime( ...
            sprintf("%02d-%d", month_index, year), ...
            'InputFormat', ...
            'MM-yyyy' ...
        ), ...
    1:12 ...
);
end



