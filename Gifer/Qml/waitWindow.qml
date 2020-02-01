import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick 2.7
import Share.core 1.0

Rectangle {
    width: getMinWidth( 400 )
    height: getMinHeight( 300 )
    color: "white"
    anchors.centerIn: parent

    Image {
        objectName: "imageObj"  // Make C++ can findChild to get the Image.
        id: iImage
        y: parent.height / 2 - 20 - iLabel.height
        anchors.horizontalCenter: parent.horizontalCenter
        width: 28 < parent.width ? 28 : parent.width
        height: 28 < parent.width ? 28 : parent.width
        cache: false            // Make WaitImageProvider::requestPixmap works.
    }

    Label {
        id: iLabel
        anchors.top: iImage.bottom
        anchors.margins: 20
        width: parent.width / 2
        anchors.horizontalCenter: parent.horizontalCenter
        text: "Please wait when software is generating gif file."
        font.pixelSize: 14
        wrapMode: Text.WordWrap
    }

    Connections
    {
        target: WaitWindowAnimation
        onWaitLogoRevolved: {
            iImage.source = "";                             // This must be entered.
            iImage.source = "image://waitImageProvider";    // Declare QQmlImageProviderBase data variable
            console.log( "onWaitLogoRevolved. " + iImage.source );
        }
    }

    function getMinHeight( _height )
    {
        if ( null !== parent )
        {
            _height = _height < parent.height ? _height : parent.height;
        }
        return _height;
    }

    function getMinWidth( _width )
    {
        if ( null !== parent )
        {
            _width = _width < parent.width ? _width : parent.width;
        }
        return _width;
    }
}
