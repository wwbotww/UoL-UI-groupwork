#include <QApplication>
#include "pages/fluor_window.hpp"
#include "pages/fluor_stats.hpp"
#include "dataset.hpp"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    // Load data (replace with actual dataset loading logic)
    WaterQualityDataset dataset;
    dataset.loadData("../data/water_quality.csv");

    // Generate fluor statistics
    FluorStats stats(dataset.filterByFluorInDefinition());

    // Create and show main window
    FluorWindow window(stats);
    window.show();

    return app.exec();
}