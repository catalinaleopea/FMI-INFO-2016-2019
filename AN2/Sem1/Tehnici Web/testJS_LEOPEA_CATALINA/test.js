var m;var N;var stats;
window.onload=function(){
	/*if(stats=localStorage.getItem("status")){
		document.body.innerHTML=status;
	}else{*/
	var dim=[8,9,10,11,12];
		for (var i=0;i<dim.length;i++) {
			var rad=document.createElement("input");
			rad.type="radio";
			rad.name="dim";
			rad.value=dim[i];

			var mij=Math.trunc(dim.length/2);
			if(i==mij) rad.checked=true;

			var label = document.createElement("label");
			label.htmlFor = dim[i];
			label.appendChild(document.createTextNode(dim[i]));

			document.body.appendChild(rad);
			document.body.appendChild(label);
		}
	var b=document.createElement("button");
	b.innerHTML="genereaza structura";
	b.id="gen_str";
	document.body.appendChild(b);
	b.onclick=function(){
		var radiouri=document.querySelectorAll("input[type=radio]");
		var labeluri=document.getElementsByTagName("label");
		for(var i=0;i<radiouri.length;i++){
			if(radiouri[i].checked==true){
				N=radiouri[i].value;
			}
			radiouri[i].style.display = "none";
			labeluri[i].style.display = "none";
		}
		b.style.display = "none";

		var ok=0;
		if(N%2==0){
			ok=1;
		}
		var m=parseInt(N)+parseInt(ok);
		var structura=document.getElementById("struct_div");
		structura.style.border="thick inset skyblue";
		structura.style.backgroundColor="skyblue";
		structura.style.width="750px";
		structura.style.height="750px";

		for(var i=0; i<m; i++){
			for(var j=0; j<N; j++){
				var d=document.createElement("div");
				d.className="patrat";
				d.dataset.lin=i;
				d.dataset.col=j;
				d.dataset.prajituri=Math.floor(Math.random() * 7);
				if(j==0){
					d.style.clear = "left";
					if(i%2==1){
						d.style.marginLeft="20px";
					}
				}
				structura.appendChild(d);
			}
		}

		var patratele=document.getElementsByClassName("patrat");
		for(var i=0;i<patratele.length;i++){
			patratele[i].style.backgroundColor="white";
			patratele[i].style.height="35px";
			patratele[i].style.width="35px";
			patratele[i].style.border = "thin solid black";
			patratele[i].style.display="inline-block";
			if(i%N==0){//linie noua
				//var br=document.createElement("br");
				patratele[i].style.display="block";
			}
		}
		//}
		structura.ondblclick=function(){
			var ok2=0;
			do{
				var pr = prompt("Introduceti lin si col separate prin virgula");
				if (pr != null) {
					var separat = pr.split(',');
					var x=parseInt(separat[0]);
					var y=parseInt(separat[1]);
					ok2=creeazaImagine(x,y);
				}
			}while(ok2!=1);

			if(ok2==1){//avem imagine pusa
				window.onkeypress=function(e) {
					var cod_ascii=e.which;
					var caracter=String.fromCharCode(cod_ascii);
					var x2=x;
					var y2=y;
					if ( caracter == "w"){
						x2=parseInt(x)-1;
						insereazaImagine(x2,y2);
						return;
					}
					if ( caracter == "e"){
						x2=parseInt(x)-1;
						y2=parseInt(y)+1;
						insereazaImagine(x2,y2);
						return;
					}
					if ( caracter == "a"){
						y2=parseInt(y)-1;
						insereazaImagine(x2,y2);
						return;
					}
					if ( caracter == "d"){
						y2=parseInt(y)+1;
						insereazaImagine(x2,y2);
						return;
					}
					if ( caracter == "z"){
						x2=parseInt(x)+1;
						insereazaImagine(x2,y2);
						return;
					}
					if ( caracter == "x"){
						x2=parseInt(x)+1;
						y2=parseInt(y)+1;
						insereazaImagine(x2,y2);
						return;
					}
				}
			}
		}
	}
}

function creeazaImagine(x,y){
	var imag=document.createElement("img");
	imag.src="http://irinaciocan.ro/tehnici_web/imagini/smiley_zambind.png";
	imag.style.height="inherit";
	imag.style.width="inherit";
	var copii=document.getElementById("struct_div").children;
	for(var i=0;i<copii.length;i++){
		if(copii[i].dataset.lin==x && copii[i].dataset.col==y){
			copii[i].appendChild(imag);
				return 1;
		}
	}
	return 0;
}

function insereazaImagine(x,y){
	var imag=document.getElementsByTagName("img")[0];
	var copii=document.getElementById("struct_div").children;
	for(var i=0;i<copii.length;i++){
		if(copii[i].dataset.lin==x && copii[i].dataset.col==y){
			copii[i].appendChild(imag);
			//alegeAleator();
			return 1;
		}
	}
	return 0;
}

function alegeAleator(){
	var d=document.createElement("div");
	d.style.border="2px solid red";
	d.style.borderRadius="inherit";
	d.style.height="inherit";
	d.style.width="inherit";
	var capat=Math.floor(Math.random() * 1);
	var par=0;var linie;
	do{
		linie=Math.floor(Math.random() * parseInt(m));
		if(parseInt(linie)%2==0){
			par=1;
		}
	}while(par!=1);
	var copii=document.getElementById("struct_div").children;
	for(var i=0;i<copii.length;i++){
		if(copii[i].dataset.lin==x && copii[i].dataset.col==y){
			copii[i].appendChild(d);
			return;
		}
	}
}

window.onbeforeunload=function(){
	var txt=document.body.innerHTML;
	localStorage.setItem("status",txt);
}