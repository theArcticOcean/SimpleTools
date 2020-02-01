import QtQuick 2.6
import QtQuick.Window 2.2
import Share.core 1.0
import QtQuick.Controls 1.4

Window {
    id: iMainWindow
    visible: true
    title: qsTr("Gifer")
    flags: Qt.CustomizeWindowHint | Qt.WindowSystemMenuHint
           | Qt.WindowCloseButtonHint | Qt.WindowMinMaxButtonsHint
           | Qt.WindowTitleHint
           | Qt.Window   | Qt.WindowStaysOnTopHint
           | Qt.WA_TransparentForMouseEvents

    // (Screen.width, Screen.height): (1440, 900)
    width: 640
    height: 480
    color: "transparent"

    onXChanged: PointManager.setLeftTopPoint( x, y )
    onYChanged: PointManager.setLeftTopPoint( x, y )

    // 23 is height of bottom buttons area, which is equal to the height of main window's title bar.
    onWidthChanged: PointManager.setRightBottomPoint( x + width, y + height - 23 )
    onHeightChanged: PointManager.setRightBottomPoint( x + width, y + height - 23 )

    Rectangle {
        anchors.fill: parent
        border.color: "yellow"
        color: "transparent"
    }

    GifWindow
    {
        id: iGifWindow
        x: parent.x
        y: parent.y
        width: parent.width
        height: parent.height - 23  // left area for bottom buttons.
    }

    Row
    {
        anchors.top: iGifWindow.bottom
        anchors.horizontalCenter: iGifWindow.horizontalCenter
        spacing: 5

        // statuc of iRecordButton: record ==> recording
        Button
        {
            id: iRecordButton
            text: "record"
            visible: iGifWindow.height > 0 && iGifWindow.width > 0
            onClicked: {
                if( "record" === text )
                {
                    text = "recording";
                }
            }
            onTextChanged: {
                if( "recording" === text )
                {
//                    // (0, 0, 1440, 824)
//                    console.log( "(" + iMainWindow.screen.virtualX + ", "
//                                + iMainWindow.screen.virtualY + ", "
//                                + iMainWindow.screen.desktopAvailableWidth + ", "
//                                + iMainWindow.screen.desktopAvailableHeight + ")");

                    WindowGrabber.startGrab( PointManager.leftTopX,  PointManager.leftTopY,
                                            PointManager.width, PointManager.height );
                    iFinishButton.text = "to finish";
                }
            }
        }

        ComboBox
        {
            id: iComboBox
            width: 70
            model: [ 30, 50, 70, 90, 110, 130, 150, 170, 190, 210, 230, 250 ]
            currentIndex: 4
            anchors.verticalCenter: parent.verticalCenter
        }

        // status of iFinishButton: finished ==> to finish ==> finished
        Button
        {
            id: iFinishButton
            text: "finished"
            visible: iGifWindow.height > 0 && iGifWindow.width > 0
            onClicked: {
                if( "recording" === iRecordButton.text )
                {
                    WaitWindowAnimation.toFinishClicked();
                }
            }
        }

        Button
        {
            id: iCloseButton
            text: "closeWindow"
            onClicked: close()
        }
    }

// signal, slot and transfer relation:
// iFinishButton::clicked ==> WaitWindowAnimation::toFinishClicked() ==> WaitWindowAnimation::show()
// WaitWindowAnimation::timer.timeout ==> WaitWindowAnimation::combineImagesTrigger
// WaitWindowAnimation::startToCombineImages ==> WindowGrabber::setFramePerSec() and combineImages()
// QSemaphore ==> ImagesCombiner::run()
// ImagesCombiner::combineImagesFinished ==> WaitWindowAnimation::hide() and WindowGrabber::saveGif()

    Connections
    {
        target: WaitWindowAnimation
        onDisappeared: {
            iRecordButton.text = "record";
            iFinishButton.text = "finished";
        }
        onStartToCombineImages: {
            WindowGrabber.setFramePerSec( iComboBox.currentText );
            WindowGrabber.combineImages();
        }
    }

    Component.onCompleted: WaitWindowAnimation.deliverMainWin( iMainWindow );
}
