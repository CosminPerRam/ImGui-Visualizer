
#include "CocktailSort.h"

void CocktailSort::sorter() {
    DO_STARTED;

    int n = numbers.size();
    bool swapped = true;
    int start = 0;
    int end = n - 1;

    while (swapped)
    {
        swapped = false;

        for (int i = start; i < end; ++i)
        {
            DO_PUT_CURSOR_AT(i + 1);
            stats.addComparison();
            if (numbers[i] > numbers[i + 1]) {
                std::swap(numbers[i], numbers[i + 1]);
                stats.addSwap();
                swapped = true;

                DO_PROGRESSIVE_CHECKSTEP;
            }
        }

        if (!swapped)
            break;

        swapped = false;

        --end;

        for (int i = end - 1; i >= start; --i)
        {
            DO_PUT_CURSOR_AT(i + 1);
            stats.addComparison();
            if (numbers[i] > numbers[i + 1]) {
                std::swap(numbers[i], numbers[i + 1]);
                stats.addSwap();
                swapped = true;

                DO_PROGRESSIVE_CHECKSTEP;
            }
        }

        ++start;
    }

    DO_FINISHED;
}
