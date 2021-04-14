import mesh3DSetup from './mesh3D'
import React from 'react';
import ReactDOM from 'react-dom';
import './style.css';

class NavTools extends React.Component {
  render(){  
    return ( [
        <div id="content">
          <input type="file" id="uploadMesh" name="uploadMesh"/>
          <progress id="progressMesh" value="1" max="100"></progress> <br/>
          <input type="button" value="Submit stl file" name="submit" onclick="{mesh3DObj.mesh3DSub}"/>
        </div>, 
        <div id="my_3d_files_converter_parent">
          <a href="https://www.weiy.city/tools/3d-files-converter/" id="my_3d_files_converter" target="_blank">3D files converter</a>
        </div>,          
        <hr id="navTopSplit"/>,

        <div id="wireframeToggleTitle"> show wireframe: </div>,
        <div id="wireframeToggle" class="close1">
            <div id="wireframeToggleCore" class="close2"></div>
        </div>
      ] );
  }
}

ReactDOM.render(
  <NavTools />,
  document.getElementById('viewer-tool')
);

mesh3DSetup();