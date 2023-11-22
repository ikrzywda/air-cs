DATA_PATH = "poland-temperature-data-2022.csv";
YEAR = 2022;
MONTH_INDEXING_ARRAY = 1:12;
MONTH_DATES_ARRAY = getDatetimeMonthArrayForYear(YEAR);
MONTH_LABELS = arrayfun(@(index) datestr(datenum(0, index, 1), 'mmmm'), MONTH_INDEXING_ARRAY, 'UniformOutput', false);


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

autocorr_result = xcorr(mean_temperature_by_month_array);

figure();
hold on;

plot(MONTH_INDEXING_ARRAY, mean_temperature_by_month_array);
plot(MONTH_INDEXING_ARRAY, mean_temperature_by_month_array, 'o');
errorbar(MONTH_INDEXING_ARRAY, mean_temperature_by_month_array, std_by_month);
xticks(MONTH_INDEXING_ARRAY);
xticklabels(MONTH_LABELS);
ylabel('Avg. temperature [C]')
hold off;

xcorr([1,2,3,4,5])

figure();
histogram(data_table.temperature);
xlabel("Temperature[C]");

figure();
histogram(mean_temperature_by_day_array);

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




