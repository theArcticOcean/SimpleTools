#include "datamanager.h"

DataManager* DataManager::instance = nullptr;

DataManager *DataManager::getInstance()
{
    if( nullptr == instance )
    {
        instance = new DataManager;
    }
    return instance;
}

DataManager::DataManager()
    : m_validImageCount( 0 )
{
    initLayouts();
}

void DataManager::initLayouts()
{
    m_layouts[0].push_back( 1 );

    m_layouts[1].push_back( 1 );
    m_layouts[1].push_back( 1 );

    m_layouts[2].push_back( 2 );
    m_layouts[2].push_back( 1 );

    m_layouts[3].push_back( 2 );
    m_layouts[3].push_back( 2 );

    m_layouts[4].push_back( 3 );
    m_layouts[4].push_back( 2 );

    m_layouts[5].push_back( 3 );
    m_layouts[5].push_back( 3 );

    m_layouts[6].push_back( 4 );
    m_layouts[6].push_back( 3 );

    m_layouts[7].push_back( 3 );
    m_layouts[7].push_back( 3 );
    m_layouts[7].push_back( 2 );

    m_layouts[8].push_back( 3 );
    m_layouts[8].push_back( 3 );
    m_layouts[8].push_back( 3 );

    m_layouts[9].push_back( 4 );
    m_layouts[9].push_back( 3 );
    m_layouts[9].push_back( 3 );

    m_layouts[10].push_back( 4 );
    m_layouts[10].push_back( 4 );
    m_layouts[10].push_back( 3 );

    m_layouts[11].push_back( 4 );
    m_layouts[11].push_back( 4 );
    m_layouts[11].push_back( 4 );

//    m_layouts[12].push_back( 5 );
//    m_layouts[12].push_back( 4 );
//    m_layouts[12].push_back( 4 );

//    m_layouts[13].push_back( 4 );
//    m_layouts[13].push_back( 4 );
//    m_layouts[13].push_back( 4 );
//    m_layouts[13].push_back( 2 );

//    m_layouts[14].push_back( 4 );
//    m_layouts[14].push_back( 4 );
//    m_layouts[14].push_back( 4 );
//    m_layouts[14].push_back( 3 );

//    m_layouts[15].push_back( 4 );
//    m_layouts[15].push_back( 4 );
//    m_layouts[15].push_back( 4 );
//    m_layouts[15].push_back( 4 );
}
