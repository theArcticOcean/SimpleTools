import * as THREE from "three"
import { OrbitControls } from "three/examples/jsm/controls/OrbitControls";
import { STLLoader } from "three/examples/jsm/loaders/STLLoader"

var output = document.getElementById( "webgl-output" );
var containerW = output.clientWidth;
var containerH = window.innerHeight;
var mesh = null;
var waitItem;
var waitImg;
var renderer;
var rayCaster;
var mousePosition;

function initRender() {
    renderer = new THREE.WebGLRenderer();
    //0x87CEFA
    renderer.setClearColor(new THREE.Color(0x000000));
    renderer.setSize(containerW, containerH);
    output.appendChild(renderer.domElement);
}

function initAssisant(){
    rayCaster = new THREE.Raycaster();
    mousePosition = new THREE.Vector2();
}

var camera;
function initCamera() {
    camera = new THREE.PerspectiveCamera(45, containerW / containerH, 0.1, 1000);
    camera.position.set( 0, 0, 30 );
    camera.lookAt( new THREE.Vector3(0,0,0) );
}

var scene;
var axesHelper;
function initScene() {
    scene = new THREE.Scene();
    axesHelper = new THREE.AxesHelper(200);
    scene.add(axesHelper);
}

//用户交互插件 鼠标左键按住旋转，右键按住平移，滚轮缩放
var controls;
function initControls() {
    controls = new OrbitControls( camera, renderer.domElement );

    // 如果使用animate方法时，将此函数删除
    //controls.addEventListener( 'change', render );
    // 使动画循环使用时阻尼或自转 意思是否有惯性
    controls.enableDamping = true;
    //动态阻尼系数 就是鼠标拖拽旋转灵敏度
    controls.dampingFactor = 0.9;
    //是否可以缩放
    controls.enableZoom = true;
    //是否自动旋转
    controls.autoRotate = false;
    controls.autoRotateSpeed = 0.5;
    //设置相机距离原点的最近距离
    controls.minDistance  = 0.1;
    //设置相机距离原点的最远距离
    controls.maxDistance  = 500;
    //是否开启右键拖拽
    controls.enablePan = true;
}

var light;
function initLights() {
    scene.add( new THREE.AmbientLight(0x444444) );
    light = new THREE.PointLight(0xffffff);
    light.position.set(0,50,50);
    //告诉平行光需要开启阴影投射
    light.castShadow = true;
    scene.add( light );
}

function render() {
    renderer.render( scene, camera );
}

function animate() {
    render();
    controls.update();

    // render using requestAnimationFrame
    requestAnimationFrame(animate);
}


function onWindowResize() {
    camera.aspect = containerW / containerH;
    camera.updateProjectionMatrix();
    render();
    renderer.setSize(containerW, containerH);
}


var lambertMaterial = new THREE.MeshLambertMaterial({
    color: 0xffffff
});
var wireFrameMat = new THREE.MeshBasicMaterial({
    opacity: 0.5,
    wireframeLinewidth: 0.5
});
wireFrameMat.wireframe = true;
function LoadSTL( path )
{
    // load the model: model from http://www.thingiverse.com/thing:69709
    var loader = new STLLoader();
    loader.load(path, function (geometry) {
        //var material = new THREE.MeshLambertMaterial({color: 0xffffff, vertexColors: THREE.FaceColors});
        mesh = new THREE.Mesh(geometry, lambertMaterial);
        geometry.center();

        console.log( path );
        // call the default render loop.
        scene.add( mesh );

        mesh.geometry.computeBoundingBox();
        const box = new THREE.Box3();
        // in the animation loop, compute the current bounding box with the world matrix
        box.copy( mesh.geometry.boundingBox ).applyMatrix4( mesh.matrixWorld );
        var bounds = [ box.min.x, box.max.x, box.min.y, box.max.y, box.min.z, box.max.z ];

        camera.lookAt( (bounds[0] + bounds[1]) / 2, (bounds[2] + bounds[3]) / 2, (bounds[4] + bounds[5])/2 );
        camera.position.set( (bounds[0] + bounds[1]) / 2, (bounds[2] + bounds[3]) / 2, (bounds[5] - bounds[4])*5 );
        camera.updateProjectionMatrix();

        HidWaiting();
        animate();
    });
}

function showWireframe( visible ) {
    if( mesh )
    {
        if( visible ) {
            mesh.material = wireFrameMat;
        }
        else {
            mesh.material = lambertMaterial;
        }
    }
}


export var mesh3DSub = function subMesh(){
    var files = document.getElementById("uploadMesh").files;
    if( files == undefined || files == "" )
    {
        alert("please choose file");
        return false;
    };


    var form = new FormData();
    form.append("fileObj", files[0]);
    var xmlRequset = new XMLHttpRequest();
    var url = "./uploadFile.php"; //to do
    xmlRequset.open("post", url, true); //post方式，url为服务器请求地址，true 该参数规定请求是否异步处理。

    xmlRequset.upload.onprogress = progressFunctionMesh;
    xmlRequset.onload = uploadCompleteMesh;
    xmlRequset.onerror = uploadFailedMesh;
    xmlRequset.send( form );
}

function uploadCompleteMesh(evt) {
    var text = evt.target.responseText;
    console.log( text )
    if( text.substr( 0, 4 ) == "url:" )
    {
        var url = text.substr( 4, text.length );
        url = "./" + url;
        console.log( url );
        scene.remove( mesh );
        LoadSTL( url );   // HidWaiting(); in call back
        render();
    }
    else
    {
        HidWaiting();
    }
}
function uploadFailedMesh(evt) {
    HidWaiting();
    alert("failed to upload file!");
}
function progressFunctionMesh(event)
{
    var value = Math.round(event.loaded / event.total * 100);
    console.log( value );
    if( value > 99 )
    {
        ShowWaiting();
    }
    document.getElementById("progressMesh").value = value;
}

function ShowWaiting() {
    waitImg.style.position = "absolute";
    var size = renderer.getSize();
    var w = parseInt( size.width / 2 - waitImg.width / 2 ) + output.offsetLeft;
    var h = parseInt( size.height / 2 - waitImg.height / 2 ) + output.offsetTop;
    console.log( w + ", " + h );
    waitImg.style.left = w.toString() + "px";
    waitImg.style.top = h.toString() + "px";
    waitItem.style.display = "block";
}

function HidWaiting() {
    waitItem.style.display = "none";
}

function ShowAxesHelper( visible ) {
    if( visible ) {
        scene.add( axesHelper );
    }
    else {
        scene.remove( axesHelper );
    }
}

function getClicked3DPoint(evt) {
    if( evt.clientX < output.offsetLeft || evt.clientY < output.offsetTop )
    {
        return null;
    }
    evt.preventDefault();
    mousePosition.x = ((evt.clientX - output.offsetLeft) / output.offsetWidth) * 2 - 1;
    mousePosition.y = -((evt.clientY - output.offsetTop) / output.offsetHeight) * 2 + 1;

    rayCaster.setFromCamera(mousePosition, camera);
    var myObjs = new Array();
    myObjs[0] = mesh;

    var intersects = rayCaster.intersectObjects(myObjs, true);
    /*An intersection has the following properties :
                - object : intersected object (THREE.Mesh)
                - distance : distance from camera to intersection (number)
                - face : intersected face (THREE.Face3)
                - faceIndex : intersected face index (number)
                - point : intersection point (THREE.Vector3)
                - uv : intersection point in the object's UV coordinates (THREE.Vector2)*/
    var resultPos = null;
    if (intersects.length > 0){
        resultPos = intersects[0].point;
        var data=[];
        data = resultPos.toArray( data );
        console.log( "resultPos: " + resultPos );
        console.log( "data: " + data );

        var str = "" + data[0] + ", " + data[1] + ", " + data[2];
        document.getElementById("pickPointResult").innerHTML = str;
        console.log( str );
    }
}

export var mesh3DSetup = function Setup()
{
    waitItem = document.getElementById('waiting');
    waitImg = document.getElementById('waitImg');

    initRender();
    initScene();
    initLights();
    initCamera();
    initControls();
    animate();
    initAssisant();
    window.onResize = onWindowResize;
    
    window.onload=function(){
        var wireDiv2=document.getElementById("wireframeToggleCore");
        var wireDiv1=document.getElementById("wireframeToggle");
        wireDiv1.onclick=function(){
            wireDiv1.className=(wireDiv1.className=="close1")?"open1":"close1";
            wireDiv2.className=(wireDiv2.className=="close2")?"open2":"close2";
          if(wireDiv1.className=="close1"){//toggle 关闭状态 切换
            showWireframe( false );
            //...
          }else{//toggle 打开状态 切换
            showWireframe( true );
          }
        }

        var axesDiv2=document.getElementById("axesVisibleCore");
        var axesDiv1=document.getElementById("axesVisibleToggle");
        axesDiv1.onclick=function(){
            axesDiv1.className=(axesDiv1.className=="close1")?"open1":"close1";
            axesDiv2.className=(axesDiv2.className=="close2")?"open2":"close2";
          if(axesDiv1.className=="close1"){//toggle 关闭状态 切换
            ShowAxesHelper( false );
            //...
          }else{//toggle 打开状态 切换
            ShowAxesHelper( true );
          }
        }

        var pickPointDiv2=document.getElementById("pickPointCore");
        var pickPointDiv1=document.getElementById("pickPointToggle");
        pickPointDiv1.onclick=function(){
            pickPointDiv1.className=(pickPointDiv1.className=="close1")?"open1":"close1";
            pickPointDiv2.className=(pickPointDiv2.className=="close2")?"open2":"close2";
          if(pickPointDiv1.className=="close1"){//toggle 关闭状态 切换
            window.removeEventListener('click', getClicked3DPoint);
            document.getElementById("pickPointResult").innerHTML = "";
          }else{//toggle 打开状态 切换
            window.addEventListener('click', getClicked3DPoint);
          }
        }
    }

    document.getElementById('subSTLButton').onclick = mesh3DSub;
}