window.onload=function(){
  	document.getElementById("st").innerHTML = 1;
  	document.getElementById("dr").innerHTML = 3;	
}

function clicked(){
	alert("Submit button clicked!");
  	var res = "output: ";
  	res = document.getElementById("nume").value;
  	res = res.concat(' ');

 	var res2 = document.getElementById("sel");
	var strUser = res2.options[res2.selectedIndex].text;
	res = res.concat(strUser);
  	res = res.concat(' ');

  	
  	
	document.getElementById("rezfinal").innerHTML = res;
}
//de facut  cu tag output nu submit