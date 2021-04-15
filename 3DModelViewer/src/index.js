import React from 'react';
import ReactDOM from 'react-dom';
import './style.css';
import * as mesh3DOBJ from './mesh3D'

class NavTools extends React.Component {
  render(){  
    return ( [
        <div key="uploadMeshContent" id="content">
          <input type="file" id="uploadMesh" name="uploadMesh"/>
          <progress id="progressMesh" value="1" max="100"></progress> <br/>
          <input id="subSTLButton" type="button" value="Submit stl file" name="submit" />
        </div>, 
        <div key="3DFilesConverter" id="my_3d_files_converter_parent">
          <a href="https://www.weiy.city/tools/3d-files-converter/" id="my_3d_files_converter" target="_blank">3D files converter</a>
        </div>,
        <hr key="navTopSplit" id="navTopSplit"/>,

        <div key="wireframeToggleTitle" id="wireframeToggleTitle"> show wireframe: </div>,
        <div key="wireframeToggle" id="wireframeToggle" className="close1">
            <div id="wireframeToggleCore" className="close2"></div>
        </div>,<br/>,<br/>,
        <div key="axesHelperTitle" id="axesHelperTitle"> show axes: </div>,
        <div key="axesVisibleToggle" id="axesVisibleToggle" className="open1">
            <div id="axesVisibleCore" className="open2"></div>
        </div>
      ] );
  }
}

class WebglApp extends React.Component{
  render(){
    return (
      <div id="waiting">
        <img src="./wait.gif" id="waitImg" alt=""/>
      </div>
    );
  }
}

ReactDOM.render(
  <NavTools />,
  document.getElementById('viewer-tool')
);

ReactDOM.render(
  <WebglApp />,
  document.getElementById('webgl-output')
);

mesh3DOBJ.mesh3DSetup();