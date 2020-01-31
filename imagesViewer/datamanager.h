#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QList>
#include <QUrl>
#include <vector>
using namespace std;

#include "macrodefined.hpp"

#define MAX_NUMBER_OF_IMAGES 12 //16

class DataManager
{
public:
    CPP_GET_MACRO( m_layouts, vector<int>* )

    static DataManager *getInstance();

    static DataManager *instance;
    QList<QUrl> m_filePaths;
    int m_validImageCount;

private:
    DataManager();
    void initLayouts();

    // m_layouts means how many cases there are, index is the number of images.
    // m_layouts[i] means i mages are put in window and the size is the number of rows.
    // m_layouts[i][j] means number of images at jth row.
    vector<int> m_layouts[ MAX_NUMBER_OF_IMAGES ];
};

#endif // DATAMANAGER_H
