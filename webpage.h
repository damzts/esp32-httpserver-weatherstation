//                    html webpage segments "variables" saved to flash
//========================================================


//========================================================
//  header, css
//========================================================
const char htmlHeader[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en" class="js-focus-visible">
<title>Monitor CICESE</title>
<style>
  table {
    position: relative;
    width:100%;
    border-spacing: 0px;
  }
  tr {
    border: 1px solid white;
    font-family: "Verdana", "Arial", sans-serif;
    font-size: 20px;
  }
  th {
    height: 20px;
    padding: 3px 15px;
    background-color: #343a40;
    color: #FFFFFF !important;
    }
  td {
    height: 20px;
    padding: 3px 15px;
  }

  table tr:first-child th:first-child {
    border-top-left-radius: 5px;
  }
  table tr:first-child th:last-child {
    border-top-right-radius: 5px;
  }
  table tr:last-child td:first-child {
    border-bottom-left-radius: 5px;
  }
  table tr:last-child td:last-child {
    border-bottom-right-radius: 5px;
  }
  .navbar {
    width: 100%;
    height: 100px;
    margin: 0;
    padding: 10px 0px;
    background-color: rgb(255, 255, 255);
    color: #000000;
    border-bottom: 5px solid #343a40;
  }
  .fixed-top {
    position: fixed;
    top: 0;
    right: 0;
    left: 0;
    z-index: 1030;
  }
  .navtitle {
    float: left;
    height: 50px;
    font-family: "Verdana", "Arial", sans-serif;
    font-size: 40px;
    font-weight: bold;
    line-height: 50px;
    padding-left: 20px;
  }
 .navheading {
   position: fixed;
   right: 0%;
   height: 20px;
   font-family: "Verdana", "Arial", sans-serif;
   font-size: 20px;
   font-weight: bold;
   line-height: 20px;
   padding-right: 20px;
   margin-right: 150px;
 }
 .navdata {
    justify-content: flex-end;
    position: fixed;
    right: 0px;
    height: 20px;
    font-family: "Verdana", "Arial", sans-serif;
    font-size: 20px;
    font-weight: bold;
    line-height: 20px;
    margin-right: 20px;
 }
 .btn {
    float: left;
    background-color: #343a40;
    border: none;
    padding: 0px 20px;
    display: inline-block;
    margin-right: 15px;
    cursor: pointer;
    height: 50px;
    font-family: "Verdana", "Arial", sans-serif;
    color: white;
    font-weight: bold;
    font-size: 18px;
    text-align: center;
    text-decoration: none;
  }
  .category {
    font-family: "Verdana", "Arial", sans-serif;
    font-weight: bold;
    font-size: 32px;
    line-height: 50px;
    padding: 20px 10px 0px 10px;
    color: #000000;
  }  
  .heading {
    font-family: "Verdana", "Arial", sans-serif;
    font-weight: normal;
    font-size: 28px;
    text-align: center;
  }
  .bodytext {
    font-family: "Verdana", "Arial", sans-serif;
    font-size: 24px;
    font-weight: light;
    border-radius: 5px;
    display:inline;
  }
  .tabledata {
    font-size: 24px;
    font-weight: bold;
    position: relative;
    padding-left: 5px;
    padding-top: 5px;
    height:   25px;
    border-radius: 5px;
    color: #000000;
    line-height: 20px;
    transition: all 200ms ease-in-out;
    background-color: #ffffff;
    text-align: center;
  }
  .container {
    max-width: 1800px;
    margin: 0 auto;
  }
  .foot {
    font-family: "Verdana", "Arial", sans-serif;
    font-size: 20px;
    position: relative;
    height:   30px;
    text-align: center;   
    color: #AAAAAA;
    line-height: 20px;
  }

  button:hover{
    background-color:orange;
  }

  button:focus{
    background-color:red;
  }

  .form-control{display:block;width:100%;padding:.375rem .75rem;font-size:1rem;font-weight:400;line-height:1.5;color:#212529;background-color:#fff;background-clip:padding-box;border:1px solid #ced4da;-webkit-appearance:none;-moz-appearance:none;appearance:none;border-radius:.25rem;transition:border-color .15s ease-in-out,box-shadow .15s ease-in-out}
  .card{position:relative;display:flex;flex-direction:column;min-width:0;word-wrap:break-word;background-color:#fff;background-clip:border-box;border:1px solid rgba(0,0,0,.125);border-radius:.25rem}
  .input-group{position:relative;display:flex;flex-wrap:wrap;align-items:stretch;width:100%}.input-group>.form-control,.input-group>.form-select{position:relative;flex:1 1 auto;width:1%;min-width:0}.input-group>.form-control:focus,    
  .btn-secondary{color:#fff;background-color:#6c757d;border-color:#6c757d;font-size: 18px;}
  .uabc{background-color: #17722b; color: #ffffff;}
  
</style>

  <body style="background-color: #efefef" onload="process()">
  
    <header>
      <div class="navbar fixed-top">
          <div class="container">

            <div class="navtitle"><svg width="100px" height="50px" viewBox="0 1 30 15" xmlns="http://www.w3.org/2000/svg" xmlns:svg="http://www.w3.org/2000/svg">
            <g id="layer1" transform="translate(-1.49977,-280.47791)">
              <path style="fill:#000000;stroke-width:0.102919" d="m 2.8435142,294.83279 c -1.5661697,-0.58763 -1.7103846,-3.47435 -0.2097035,-4.19757 0.3297324,-0.1589 0.6577217,-0.1978 1.6833759,-0.19968 l 1.2738519,-0.003 v 0.42407 0.42408 H 4.5887301 c -1.6110361,0 -2.0659456,0.36284 -1.9714174,1.57245 0.038292,0.48998 0.096385,0.63171 0.3622778,0.88381 0.3087251,0.29272 0.3454609,0.30025 1.4640597,0.30025 h 1.1473883 v 0.47709 0.47709 l -1.1739427,-0.005 c -0.7462127,-0.003 -1.319551,-0.0592 -1.5735816,-0.15459 z m 3.5468033,-2.12015 v -2.27943 h 0.4995493 0.4995506 v 2.27943 2.27941 H 6.8898668 6.3903175 Z m 2.8518704,2.11092 c -0.8559375,-0.33257 -1.1534017,-0.8929 -1.1534017,-2.17261 0,-1.00829 0.1909987,-1.4787 0.7720473,-1.9015 0.3363854,-0.24476 0.4621563,-0.26577 1.7930575,-0.29968 l 1.431294,-0.0364 v 0.43402 0.43403 h -1.052264 c -1.6617678,0 -1.9450349,0.2163 -1.9450349,1.48526 0,0.50579 0.045407,0.67938 0.2408894,0.92076 0.2368123,0.29243 0.2621703,0.29806 1.4986475,0.33262 l 1.257762,0.0352 v 0.46844 0.46845 l -1.223897,-0.008 c -0.803755,-0.005 -1.3595639,-0.0602 -1.6191001,-0.16103 z m 4.0630871,-0.0568 c -0.65847,-0.34586 -0.914676,-1.12885 -0.585436,-1.78918 0.110924,-0.22245 0.108906,-0.31469 -0.0126,-0.57416 -0.184477,-0.39394 -0.110758,-1.15989 0.140433,-1.45912 0.352535,-0.42 0.750602,-0.51118 2.231602,-0.51118 h 1.401949 v 0.42407 0.4241 h -1.279734 c -1.444594,0 -1.656014,0.0777 -1.60125,0.58832 l 0.03355,0.31283 1.423717,0.0295 1.423717,0.0295 v 0.42115 0.42117 H 15.15242 c -0.900299,0 -1.367463,0.0411 -1.448692,0.12722 -0.173691,0.18432 -0.148569,0.68656 0.03814,0.76261 0.08692,0.0354 0.738832,0.0643 1.448694,0.0643 h 1.290658 v 0.47708 0.4771 l -1.373762,-9e-5 c -1.198939,-7e-5 -1.428283,-0.0287 -1.802187,-0.22511 z m 4.075137,-0.2519 v -0.47707 h 1.428713 c 1.461822,0 1.668496,-0.0531 1.668496,-0.42886 0,-0.41354 -0.313046,-0.52531 -1.471189,-0.52531 h -1.105769 l -0.310082,-0.37477 c -0.573298,-0.69288 -0.343804,-1.77634 0.45089,-2.12869 0.232844,-0.10319 0.778967,-0.14704 1.83348,-0.14704 h 1.501859 v 0.42407 0.4241 h -1.355352 c -1.406275,0 -1.741856,0.0807 -1.741856,0.41913 0,0.50263 0.06789,0.53503 1.121073,0.53503 0.839893,0 1.0613,0.0367 1.38443,0.22941 0.922213,0.55001 0.895389,1.82546 -0.04858,2.31037 -0.366216,0.18813 -0.61552,0.21674 -1.889001,0.21674 H 17.38042 Z m 5.341928,0.2653 c -0.678145,-0.3562 -0.96144,-1.21707 -0.587132,-1.78414 0.145314,-0.22015 0.145314,-0.27127 0,-0.59622 -0.21324,-0.47686 -0.199632,-0.88736 0.04343,-1.31044 0.315142,-0.54849 0.691469,-0.65624 2.292159,-0.65624 h 1.401949 v 0.42407 0.4241 h -1.255442 c -1.309771,0 -1.641947,0.0847 -1.641947,0.41913 0,0.5223 0.03592,0.53503 1.509338,0.53503 h 1.388051 v 0.42408 0.42409 h -1.291692 c -1.356824,0 -1.605697,0.0799 -1.605697,0.51645 0,0.38111 0.202812,0.43772 1.568587,0.43772 h 1.328802 v 0.47707 0.47711 l -1.373762,-9e-5 c -1.17161,-6e-5 -1.433047,-0.0312 -1.776656,-0.21172 z M 9.4375716,288.79189 c -0.6670759,-0.17841 -1.1545275,-0.396 -2.4085239,-1.07523 -0.578829,-0.31354 -1.1166941,-0.57005 -1.1952576,-0.57005 -0.078566,0 -0.1428426,-0.0387 -0.1428426,-0.0859 0,-0.0471 0.8137865,-0.14032 1.808414,-0.20682 1.8951222,-0.12672 2.2041873,-0.21456 2.3388467,-0.66479 0.096018,-0.32104 -0.116282,-1.14352 -0.4600244,-1.7822 -0.2934591,-0.54525 -0.3050211,-0.55363 -0.6691209,-0.48377 l -0.3705014,0.0711 0.2397638,-0.27636 c 0.3084243,-0.3555 0.1103571,-0.46588 -0.4166789,-0.23221 -0.4074673,0.18067 -0.9300191,0.21428 -1.0167306,0.0653 -0.031059,-0.0534 0.2023235,-0.18851 0.5186316,-0.30039 0.3163071,-0.11195 0.552624,-0.24717 0.525149,-0.30061 -0.056205,-0.10932 -0.1703832,-0.10857 -1.1207428,0.008 -0.4940939,0.0606 -0.7576652,0.0436 -0.9990998,-0.0643 l -0.3279505,-0.14665 0.4995494,-0.0704 c 0.2747519,-0.0387 0.7243467,-0.0761 0.9990997,-0.083 0.4617244,-0.0113 0.484865,-0.0244 0.3056112,-0.16831 -0.1365635,-0.10956 -0.4552554,-0.15566 -1.0772407,-0.15566 -0.9425489,0 -1.3988617,-0.13701 -1.7166272,-0.51546 l -0.1903272,-0.22667 1.4392024,0.004 c 1.6533521,0.004 2.4267825,0.14874 3.3340129,0.62268 1.1355252,0.59319 1.8894662,1.39763 2.5804912,2.75329 0.420212,0.82438 0.990735,1.46799 1.407985,1.58837 0.46299,0.13355 0.541359,0.0101 0.134303,-0.21139 -0.419857,-0.22858 -0.595016,-0.4775 -1.175792,-1.67093 -0.554103,-1.13862 -1.306412,-2.00477 -2.139312,-2.463 -0.3530572,-0.19426 -0.6303463,-0.36548 -0.616197,-0.38048 0.014154,-0.015 0.3594756,0.0709 0.767388,0.19079 0.993154,0.29204 1.824071,0.77771 2.288554,1.33767 0.363282,0.43794 0.492555,0.67699 0.862759,1.5954 0.539925,1.33945 0.755376,1.61681 1.25601,1.61681 0.663414,0 1.091725,-0.5248 1.286721,-1.57655 l 0.120487,-0.64987 h 0.674169 c 0.70355,0 1.168822,0.14923 1.607766,0.51565 0.245474,0.20494 0.414398,0.2186 3.067389,0.24818 2.079761,0.0231 2.839947,0.0656 2.932345,0.16383 0.09978,0.10608 -0.469243,0.13253 -2.844735,0.13253 h -2.969468 l -0.374155,-0.26273 c -0.944398,-0.66319 -1.432895,-0.43282 -2.197735,1.03648 -0.797316,1.53167 -1.658099,2.28519 -3.068738,2.68634 -0.627529,0.17844 -2.812087,0.17067 -3.4968474,-0.0125 z m -4.4902832,-1.13877 c -0.1953613,-0.29597 -0.1992732,-0.50651 -0.00945,-0.50651 0.1605042,0 1.1289667,0.35636 1.6023074,0.58961 0.2829979,0.13944 0.2512454,0.14785 -0.5688165,0.15012 -0.7856379,0.003 -0.8833935,-0.02 -1.0240777,-0.23322 z m 11.8836176,0.0432 c -0.604431,-0.21967 -0.825355,-0.61627 -0.600411,-1.07786 0.376186,-0.77195 0.861759,-0.86436 4.347036,-0.82735 l 2.847433,0.0303 -0.899189,0.33152 c -0.494554,0.18233 -1.348784,0.50078 -1.89829,0.70767 -1.939483,0.7302 -3.276886,1.02462 -3.796579,0.83577 z m 0.319099,-2.31382 c -0.10638,-0.11295 0.02695,-0.24509 0.183077,-0.18152 0.08035,0.0327 0.121218,0.10218 0.09081,0.1544 -0.06475,0.1112 -0.183571,0.12297 -0.273892,0.0272 z" id="path3281" />
            </g>  
            </svg></div>
          
            <div class="navtitle">Estacion Meteorologica</div> 
            <div class="navdata" id = "date">mm/dd/yyyy</div>
            <div class="navheading">FECHA:</div><br>
            <div class="navdata" id = "time">00:00:00</div>
            <div class="navheading">HORA:</div>

            <div class="navtitle fixed-top" style="margin-top:60px">
            <a href='/'> <button class = "btn" > Inicio </button> </a>
            <a href='/dir'> <button class = "btn" > Directorio </button> </a>
            <a href='/stream'> <button class = "btn" > Visualizar </button> </a>
            <a href='/delete'> <button class = "btn" > Eliminar </button> </a>
            <a href='/config'> <button class = "btn" > Configuracion </button> </a>

            <table  style="width:20%; right:0px; margin-right: 20px; position: fixed; border-radius: 5px;">
              <colgroup>
                <col span="1" style="background-color:rgb(230, 230, 230); width: 100%; color:#ffffff ;">
              </colgroup>
              <tr>
                <td><div class="tabledata" id = "bat">...</div></td>
              </tr>
            </table>
            
            </div>
            
          </div>
      </div>
    </header>
    <main class="container" style="margin-top:100px ">
)=====";
//========================================================
//  temperature reading display  
//========================================================
const char homebody[] PROGMEM = R"=====(
  <div class="category">Lecturas</div>
    <table style="width:100%">
      <colgroup>
        <col span="1" style="background-color:rgb(230,230,230); width: 30%; color:#000000 ;">
        <col span="1" style="background-color:rgb(215,215,215); width: 80%; color:#000000 ;">
      </colgroup>
      <tr>
        <th colspan="1"><div class="heading">Parametro</div></th>
        <th colspan="1"><div class="heading">Valor</div></th>
      </tr>
      <tr>
        <td><div class="bodytext">Temperatura (C)</div></td>
        <td><div class="tabledata" id = "b0"></div></td>
      </tr>
      <tr>
        <td><div class="bodytext">Humedad (%)</div></td>
        <td><div class="tabledata" id = "b1"></div></td>
      </tr>
      <tr>
        <td><div class="bodytext">Presion (hPa)</div></td>
        <td><div class="tabledata" id = "b2"></div></td>
      </tr>
    </table>

    <div class="category" style= "margin:0 auto;" >Ajustar hora</div>
      <table style="width:50%; ">
        <colgroup>
          <col span="1" style="background-color:rgb(230,230,230); width: 20%; color:#000000 ;">
          <col span="1" style="background-color:rgb(200,200,200); width: 50%; color:#000000 ;">
          <col span="1" style="background-color:rgb(200,200,200); width: 10%; color:#000000 ;">
        </colgroup>
        <tr>
          <th colspan="1"><div class="heading">Reloj</div></th>
          <th colspan="1"><div class="heading"></div></th>
          <th colspan="1"><div class="bodytext"></div></th>
        </tr>
        <tr>
          <td><div class="bodytext">Fecha:</div></td>
          <td><div class="tabledata" id= "b3">dd/mm/yyyy</div></td>
          <td><span id="syncresponse"></span></td>
        </tr>
        <tr>
          <td><div class="bodytext">Hora:</div></td>
          <td><div class="tabledata" id = "b4" >hh:mm:ss</div></td>
          <td><button type="button" class = "btn-secondary" onclick="syncdatetime()">Actualizar</button></td>
        </tr>
        </table>
        
)=====";

//========================================================
// handle directory buttons
//========================================================
const char dirbody[] PROGMEM = R"=====(
  <div class='category'>Directorio</div>

  <div class="bodytext" style= "margin:0 auto;">Crear nuevo archivo</div>
  <form class="card" style="width:40%;" onsubmit="jsnewfile(); return false;"><div class="input-group">
    <input type="text" class="form-control" placeholder="Nombre.csv" id="newfilenameid" value="" onfocus="activefiledisplay()">
    <button type="button" class="btn-secondary" onclick="jsnewfile()">Entrar</button></div>
    <span id="activefiledisplayid"></span>
    <span id="newfileupdateid"></span>
  </form>

  <div class='heading'>Contenido en Tarjeta SD</div><br>
  <table>
  <colgroup>
    <col span='1' style='background-color:rgb(230,230,230); width: 20%; color:#000000;'>
    <col span='1' style='background-color:rgb(150,150,150); width: 55%; color:#000000 ;'>
    <col span='1' style='background-color:rgb(150,150,150); width: 35%; color:#000000 ;'>
    <col span='1' style='background-color:rgb(255, 236, 206); width: 5%; color:#000000 ;'>
  </colgroup>
  <tr>
    <th><div class='heading'>Nombre</div></th>
    <th><div class='heading'>Tipo</div></th>
    <th><div class='heading'>Volumen</div></th>
    <th><div class='heading'>Descarga</div></th>
  </tr>
)=====";

//========================================================
// handle configurations
//========================================================
const char confbody[] PROGMEM = R"=====(
      <div class="category">Configuracion</div>
      <div class="bodytext" style= "margin:0 auto;" >Ubicacion del dispositivo</div>
      <form class="card" style="width:40%;" onsubmit="csvtitleresponse(); return false;"><div class="input-group">
          <input type="text" class="form-control" placeholder="Nombre..." id="jscsvtitleid" value="" onfocus="csvtitledisplay()">
          <button type="button" class="btn-secondary" onclick="csvtitleresponse()">Entrar</button></div>
          <span id="csvtitledisplayid"></span>
          <span id="titleupdateid"></span>
      </form>
      
      <div class="category"></div>
      <div class="bodytext" style= "margin:0 auto;">Tiempo de muestreo (2-3600)</div>
      <form class="card" style="width:20%;" onsubmit="sleeptimeresponse(); return false;"><div class="input-group">
        <input type="text" class="form-control" placeholder="Segundos..." id="jssleeptimeid" value="" onfocus="sleeptimedisplay()">
        <button type="button" class="btn-secondary" onclick="sleeptimeresponse()">Entrar</button></div>
        <span id="sleeptimedisplayid"></span>
        <span id="timeupdateid"></span>
      </form>

)=====";

//========================================================
// end container, footer & JavaScript
//========================================================
const char htmlFooter[] PROGMEM = R"=====(
</main>
<div class="category"> </div>
<footer div class="foot" id = "temp" >Estacion Meteorologica UABC - CICESE 2022</div></footer>
</body>
<script type = "text/javascript">
  
    // function to create XML object
    function createXmlHttpObject(){
      if(window.XMLHttpRequest){
        xmlHttp=new XMLHttpRequest();
      }
      else{
        xmlHttp=new ActiveXObject("Microsoft.XMLHTTP");
      }
      return xmlHttp;
    }
    
    // general processing code for the web page to ask for an XML stream
    function process(){
      // global variable visible to all java functions
      var xmlHttp=createXmlHttpObject();
     
      if(xmlHttp.readyState==0 || xmlHttp.readyState==4) {
        xmlHttp.onreadystatechange=response;
        xmlHttp.open("PUT","xml",true);
        xmlHttp.send();
      }       
      // you may have to play with this value, big pages need more porcessing time, and hence
      // a longer timeout
      setTimeout("process()",200);
    }
    
    // function to handle the response from the ESP
    function response(){
      var message;
      var xmlResponse;
      var xmldoc;
      var dt = new Date();
      
      var color = "#e8e8e8";
      var barwidth;
      
      try{
        if (xmlHttp.status == 200) {
          // get the xml stream
          xmlResponse=xmlHttp.responseXML;
      
          // get host date and time
          document.getElementById("time").innerHTML = dt.toLocaleTimeString([], { hour12: false });
          document.getElementById("date").innerHTML = dt.toLocaleDateString(['en-GB']);

           // Bat
          xmldoc = xmlResponse.getElementsByTagName("B5");
          message = xmldoc[0].firstChild.nodeValue;
          if (message<25){color = "ff4646";}else if(message<50){color = "#ffbb46";}else if(message<95){color = "#00ff46";}else{color = "#0046ff";}
          barwidth = message;
          document.getElementById("bat").innerHTML=message;
          document.getElementById("bat").style.width=(barwidth+"%");
          document.getElementById("bat").style.backgroundColor=color;
          document.getElementById("bat").style.borderRadius="5px";
          console.log(message);
          
          // B0
          xmldoc = xmlResponse.getElementsByTagName("B0"); 
          message = xmldoc[0].firstChild.nodeValue;
          if (message<10){color = "#adebff";}else if(message<15){color = "#ebe7ca";}else if(message<20){color = "#e6a777";}else if(message<25){color = "#e69377";}else if(message<30){color = "#e68477";}else{color = "#de6f6f";}
          barwidth = (message * 100) / 85.0;
          document.getElementById("b0").innerHTML=message;
          document.getElementById("b0").style.width=(barwidth+"%");
          document.getElementById("b0").style.backgroundColor=color;
          document.getElementById("b0").style.borderRadius="5px";

          // B1
          xmldoc = xmlResponse.getElementsByTagName("B1"); 
          message = xmldoc[0].firstChild.nodeValue;
          if (message<25){color = "#b9e3eb";}else if(message<50){color = "#7ec8d9";}else if(message<95){color = "#4799c9";}else{color = "#0c72ad";}
          barwidth = message;
          document.getElementById("b1").innerHTML=message;
          document.getElementById("b1").style.width=(barwidth+"%");
          document.getElementById("b1").style.backgroundColor=color;
          document.getElementById("b1").style.borderRadius="5px";

          // B2
          xmldoc = xmlResponse.getElementsByTagName("B2"); 
          message = xmldoc[0].firstChild.nodeValue;
          if (message<1000){color = "#f5f2e4";}else if(message<1010){color = "#ece3ba";}else if(message<1020){color = "#f5e499";}else{color = "#e6cf6d";}
          barwidth = (message*100) / 1100.0;
          document.getElementById("b2").innerHTML=message;
          document.getElementById("b2").style.width=(barwidth+"%");
          document.getElementById("b2").style.backgroundColor=color;
          document.getElementById("b2").style.borderRadius="5px";

          // B3
          xmldoc = xmlResponse.getElementsByTagName("B3"); 
          message = xmldoc[0].firstChild.nodeValue;
          document.getElementById("b3").innerHTML=message;
          document.getElementById("b3").style.borderRadius="5px";
       
          // B4
          xmldoc = xmlResponse.getElementsByTagName("B4");
          message = xmldoc[0].firstChild.nodeValue;
          document.getElementById("b4").innerHTML=message;
          document.getElementById("b4").style.borderRadius="5px";
          
        }
      }catch( e ){}
    } 
    
    function syncdatetime() {
      var xhttp = new XMLHttpRequest();
      var dt = new Date();
      var options = {weekday: 'long'};
      var value = dt.toLocaleDateString(['en-GB']);
      var value2 = dt.toLocaleDateString(['en-GB'],options);
      var value3 = dt.toLocaleTimeString([], { hour12: false });


      xhttp.onreadystatechange = function(){
        if (this.readyState == 4 && this.status == 200) {
          // update the web based on reply from  ESP
          document.getElementById("syncresponse").innerHTML=this.responseText;
        }
      }
        
      xhttp.open("PUT", "syncdatetime?VALUE="+value+"&VALUE2="+value2+"&VALUE3="+value3, true);
      xhttp.send();
    }

    function csvtitleresponse(){
      var value = document.getElementById("jscsvtitleid").value;
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function(){
        if(this.readyState == 4 && this.status == 200) {
          // update the web based on reply from  ESP
          document.getElementById("titleupdateid").innerHTML=this.responseText;
        }
      }
      xhttp.open("PUT", "updtitle?VALUE="+value, true);
      xhttp.send();    
    }

    function sleeptimeresponse(){
      var value = document.getElementById("jssleeptimeid").value;
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function(){
        if(this.readyState == 4 && this.status == 200){
          // update the web based on reply from  ESP
          document.getElementById("timeupdateid").innerHTML=this.responseText;
        }
      }
      xhttp.open("PUT", "updtime?VALUE="+value, true);
      xhttp.send();  
    }

    function jsnewfile(){
      var value = document.getElementById("newfilenameid").value;
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function(){
        if(this.readyState == 4 && this.status == 200){
          // update the web based on reply from  ESP
          document.getElementById("newfileupdateid").innerHTML=this.responseText;
        }
      }
      xhttp.open("PUT", "newfile?VALUE="+value, true);
      xhttp.send();  
    }

    function csvtitledisplay(){
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function(){
        if(this.readyState == 4 && this.status == 200){
          // update the web based on reply from  ESP
          document.getElementById("csvtitledisplayid").innerHTML=this.responseText;
        }
      }
      xhttp.open("PUT", "titledisplay", true);
      xhttp.send();  
    }

    function sleeptimedisplay(){
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function(){
        if(this.readyState == 4 && this.status == 200){
          // update the web based on reply from  ESP
          document.getElementById("sleeptimedisplayid").innerHTML=this.responseText;
        }
      }
      xhttp.open("PUT", "sleeptimedisplay", true);
      xhttp.send();  
    }

    function activefiledisplay(){
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function(){
        if(this.readyState == 4 && this.status == 200){
          // update the web based on reply from  ESP
          document.getElementById("activefiledisplayid").innerHTML=this.responseText;
        }
      }
      xhttp.open("PUT", "activefiledisplay", true);
      xhttp.send();  
    }
  </script>
</html>
)=====";
