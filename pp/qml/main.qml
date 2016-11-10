/*
* Project: PiOmxTextures
* Author:  Luca Carlon
* Date:    07.13.2013
*
* Copyright (c) 2012, 2013 Luca Carlon. All rights reserved.
*
* This file is part of PiOmxTextures.
*
* PiOmxTextures is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* PiOmxTextures is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with PiOmxTextures. If not, see <http://www.gnu.org/licenses/>.
*/

import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.0
import QtMultimedia 5.0

import PianoKeyboard 1.0
import PianoRoll 1.0
import "POC_StringUtils.js" as POC_StringUtils

Rectangle {
    width: 1480
    height: 800
    id:     mainView
    color:  "white"
    focus:  true

//    // The unique media player.
//    MediaPlayer {
//        objectName: "mediaPlayer"
//        id: mediaPlayer
//        autoLoad: true
//        autoPlay: false
//        function playPause() {
//            if (mediaPlayer.playbackState === MediaPlayer.PlayingState)
//                mediaPlayer.pause();
//            else if (mediaPlayer.playbackState === MediaPlayer.PausedState)
//                mediaPlayer.play();
//            else if (mediaPlayer.playbackState === MediaPlayer.StoppedState)
//                mediaPlayer.play();
//        }
//        function volumeUp() {
//            volume = (volume + 0.1 > 1) ? 1 : volume + 0.1;
//        }
//        function volumeDown() {
//            volume = (volume - 0.1 < 0) ? 0 : volume - 0.1;
//        }
//        // Only used for debugging purposes.
//        onStopped: {
//            console.log("Stopped signal received!");
//        }
// //   Component.onCompleted:{mediaOutput.showVideo("file:///home/pi/jg.mov");mediaPlayer.pause();}

//    }
//    Slider {
//        id: sliderPosition
//        y:600
//        width:1480
//        height:200
//        Layout.alignment:         Qt.AlignVCenter | Qt.AlignHCenter
//        Layout.fillWidth: true
//        maximumValue:             1.0
//        minimumValue:             0.0
//        stepSize:                 0.01
//        value: mediaPlayer.position/mediaPlayer.duration;
//        updateValueWhileDragging: false

//        // NOTE: Remember to avoid seeking on value changed. That will result in
//        // seeking for every set of the value prop.
//        onValueChanged: pianoroll.syncTime(mediaPlayer.position);
//    }
////     Generic media output for images, videos and audio.
//    POC_MediaOutput {
//        objectName: "mediaOutput"
//        id: mediaOutput

//        onControlBarDismissed: parent.focus = true
//    }
//    // These are shortcuts for common functionalities.
//    Keys.onPressed: {


//        if (event.key === Qt.Key_S)
//            mediaPlayer.stop();
//        else if (event.key === Qt.Key_P)
//            mediaPlayer.playPause();
//        else if (event.key === Qt.Key_Plus)
//            mediaPlayer.volumeUp();
//        else if (event.key === Qt.Key_Minus)
//            mediaPlayer.volumeDown();
//        else if(event.key===Qt.Key_Return) {
//            mediaOutput.showVideo("file:///home/pi/jg.mov");
//            mediaPlayer.pause();
//        }
//        else
//            return;

//        event.accepted = true;
//    }
    Keys.onPressed: {
        if(event.key===Qt.Key_Space)
        {
            console.log("space Pressed");
            pianoroll.continuePlay();
        }
    }
    Item{
        x:0
        y:0
        width:1480
        height:900
        PianoRoll{
            id:pianoroll
            x:0
            y:0
            width:1480
            height:700
            widthd:1480
            heightd:700
            anchors.centerIn: parent
            onNoteOn:keyboard.noteOn(note);
            onNoteOff:keyboard.noteOff(note);
//            onStartPlay:mediaPlayer.play();
//            Component.onCompleted: {mediaOutput.showVideo("file:///home/pi/jg.mov");mediaPlayer.pause();}

        }

        PianoKeyboard {
            id:keyboard
            x:0
            y:704
            width: 1480
            height: 200
            onKeyPress:pianoroll.keyPress(note);
        }
    }
//    Item {

////        Component.onCompleted:keyboard.update();
//    }
}

