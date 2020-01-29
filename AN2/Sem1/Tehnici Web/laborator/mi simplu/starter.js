var ultimSrc;
var ultimBorder;
var optFluture;
var optBorder;
window.onload=function() {
	var s=document.getElementById("sel");
	var imag=document.getElementById("imag");
	var opt=document.querySelectorAll("option");
	var radiouri=document.querySelectorAll("input[type=radio]");

	s.onchange=function() {	
		for (var i=0;i<opt.length;i++) {
			if (opt[i].selected==true) {
				var sursa=opt[i].value;
				localStorage.setItem("src",sursa);
				localStorage.setItem("F",i);
			}
		}
		imag.src=sursa;
	}
	
	var butoane=document.getElementsByTagName("div")[0];
	for (var i=0;i<radiouri.length;i++){
		radiouri[i].onchange=function(){
			for (var j=0;j<radiouri.length;j++){
				if (radiouri[j].checked==true){
					imag.style.borderStyle="solid";
					var culoare=radiouri[j].value;
					imag.style.borderColor=culoare;
					localStorage.setItem("border",culoare);
					localStorage.setItem("B",j);
				}
			}
		}
	}

	if (ultimSrc=localStorage.getItem("src"))
		imag.src=ultimSrc;
	if (ultimBorder=localStorage.getItem("border")){
		imag.style.borderStyle="solid";
		imag.style.borderColor=ultimBorder;
	}
	if (optFluture=localStorage.getItem("F")){
		var nr=parseInt(optFluture);
		opt[nr].selected=true;
	}
	if (optBorder=localStorage.getItem("B")){
		var nr2=parseInt(optBorder);
		radiouri[nr2].checked=true;
	}

	imag.onclick=function() {
		if (event.ctrlKey) {
			this.style.borderStyle="hidden";
			this.style.borderColor="transparent";
			ultimBorder=null;
			optBorder=-1;
			localStorage.removeItem("border");
			localStorage.removeItem("B");
		}
	}
	
}