var N = 4, min = 0, max = 100;
var n1, n2;
function a(){
  n1 = Math.floor(Math.random() * (max - min + 1)) + min;
  n2 = Math.floor(Math.random() * (max - min + 1)) + min; 
  var res = "";
  res = res.concat(n1);
  res = res.concat(" + ");
  res = res.concat(n2);
  res = res.concat(" = ");
  document.getElementById("intrebare_text").innerHTML = res;
}

function vera(){
  var rezultat = document.getElementById("adunare");
  var rez = rezultat.value;
  if(rez == (n1 + n2)){
    document.getElementById("rez").innerHTML = "corect";
    nr_raspunsuri_corecte++;
  }else{
    document.getElementById("rez").innerHTML = "gresit";
  }
}

function b(){
  var res = "";
  var n = 0, m = 5;
  var a = Math.floor(Math.random() * (5 - (-5) + 1)) - 5;
  while(a == 0){
    a = Math.floor(Math.random() * (5 - (-5) + 1)) - 5;
  }
  var b = Math.floor(Math.random() * (5 - (-5) + 1)) - 5;
  for (var i = 0; i < m; i++ , n++){
    res = res.concat(a * n + b);
    res = res.concat(",");
  }
  res = res.concat("...");
  document.getElementById("intrebare_radio").innerHTML = res;
  document.getElementById("rp1").innerHTML = a * (n - 1) + b;
  document.getElementById("radiobut1").value = a * (n - 1) + b;
    
  document.getElementById("rp2").innerHTML = a * n + b;
  document.getElementById("radiobut2").value = a * n + b;

  document.getElementById("rp3").innerHTML = a * (n + 1) + b;
  document.getElementById("radiobut3").value = a *(n + 1) + b;

  document.getElementById("rp4").innerHTML = Math.floor(Math.random() * (b * n - a + 1)) + a;
  document.getElementById("radiobut4").value = Math.floor(Math.random() * (b * n - a + 1)) + a;
}

function verb(){
  if(document.getElementById("radiobut2").checked) {
    document.getElementById("rez2").innerHTML = "corect";
    nr_raspunsuri_corecte++;
  }else{
    document.getElementById("rez2").innerHTML = "gresit";
  }
}

function c(){
  var res = "Care dintre literele de mai jos sunt mai mari decat ";
  var possible = "abcdefghijklmnopqrstuvwxyz";
  var lit = possible.charAt(Math.floor(Math.random() * possible.length));
  res = res.concat(lit);
  res = res.concat("?");
  document.getElementById("intrebare_checkbox").innerHTML = res;
}

function verc(){

}

function d(){
  var m1 = Math.floor(Math.random() * (max - min + 1)) + min;
  var m2 = Math.floor(Math.random() * (max - m1 + 1)) + m1;
  if(m1 %2 != m2 % 2){
    m2--;
  }
  document.getElementById("st").innerHTML = m1;
  document.getElementById("dr").innerHTML = m2;
}

function verd(){
    res = "=";
  res = res.concat(1);
  document.getElementById("rez4").innerHTML = res;
}

function generateN(){
  for(var i=0;i<N;i++){
    var x =Math.floor(Math.random() * (4 - 1 + 1)) + 1;
    switch(x){
      case 1:{
        a();
        break;
      }
      case 2:{
        b();
        break;
      }
      case 3:{
        c();
        break;
      }
      case 4:{
        d();
        break;
      }
    }
  }
}

window.onload = function(){
  a();
  b();
  c();
  d();
}

//verificare
function clicked(){
  alert("Submit button clicked!");
  var nr_raspunsuri_corecte = 0;

  vera();
  verb();
  verc();
  verd();

  res = "Scorul este ";
  res = res.concat(nr_raspunsuri_corecte / N);
  document.getElementById("rezfinal").innerHTML = res;
}
