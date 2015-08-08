(function() {
  loadOptions();
  submitHandler();
})();

function getQueryParam(variable, defaultValue) {
  // Find all URL parameters
  var query = location.search.substring(1);
  var vars = query.split('&');
  for (var i = 0; i < vars.length; i++) {
    var pair = vars[i].split('=');

    // If the query variable parameter is found, decode it to use and return it for use
    if (pair[0] === variable) {
      return decodeURIComponent(pair[1]);
    }
  }
  return defaultValue || false;
}

function submitHandler(){
	var $submitButton = $('#submitButton');

	$submitButton.on('click', function(){
		var $lightOffColorPicker = $('#lightOffColorPicker');
		var $lightOnColorPicker = $('#lightOnColorPicker');
		var $backgroundColorPicker = $('#backgroundColorPicker');
		var params = {
			background : $backgroundColorPicker.val(),
			letter_on : $lightOnColorPicker.val(),
			letter_off : $lightOffColorPicker.val()
		}
		console.log(params);
		var return_to = getQueryParam('return_to', 'pebblejs://close#');
		document.location = return_to + encodeURIComponent(JSON.stringify(params));;
	});
}

function loadOptions(){
	var $lightOffColorPicker = $('#lightOffColorPicker');
	var $lightOnColorPicker = $('#lightOnColorPicker');
	var $backgroundColorPicker = $('#backgroundColorPicker');
	var settings = {
		letter_off: "0x545454",
		letter_on: "0xFFFFFF",
		background: "0x000000"
	}
	if (decodeURIComponent(window.location.hash.substring(1)) != ""){
		var temp = JSON.parse(decodeURIComponent(window.location.hash.substring(1)));
		settings.letter_off = "0x" + pad(new Number(temp.letter_off).toString(16),6);
		settings.letter_on = "0x" + pad(new Number(temp.letter_on).toString(16),6);
		settings.background = "0x" + pad(new Number(temp.background).toString(16),6);
	}
	console.log(settings)
	//letter_off
	//getStyleSheet().cssRules[1].style.color = "#" + pad(new Number(settings.letter_off).toString(16),6);
	$lightOffColorPicker[0].value = settings.letter_off;
	//letter_on
	//getStyleSheet().cssRules[2].style.color = "#" + pad(new Number(settings.letter_on).toString(16),6);
	$lightOnColorPicker[0].value = settings.letter_on;
	//background
	//getStyleSheet().cssRules[0].style.background = "#" + pad(new Number(settings.background).toString(16),6);
	$backgroundColorPicker[0].value = settings.background;
}

function getStyleSheet(){
	var res;
	for (var i=0; i < document.styleSheets.length; i++){
		if (document.styleSheets[i].title == "myStyle"){
			res = document.styleSheets[i];
			break;
		}
	}
	return res;
}
/*document.addEventListener('click', function(e) {
    e = e || window.event;
    var target = e.target || e.srcElement;
    if (target.localName == "polygon"){
	   var radios = document.getElementsByName("choice")
	   for (var j = 0, length = radios.length; j < length; j++) {
		if (radios[j].checked) {
			choice =radios[j].value

			// only one radio can be logically checked, don't check the rest
			break;
			}
		}
	    
		var rule = getStyleSheet().cssRules[choice];
		if (choice == 1){
			rule.style.setProperty("color",target.attributes.fill.value);
		}
		else if (choice==2){
			rule.style.setProperty("color",target.attributes.fill.value);
		}
		else if (choice==0){
			rule.style.setProperty("background",target.attributes.fill.value);
		}
		choice++;
		if (choice>=3){
			choice = 0;
		}

		radios[choice].checked = true
	}
}, false);*/
function pad(num, size) {
    var s = num+"";
    while (s.length < size) s = "0" + s;
    return s;
}
function toHex(num){
	return pad(new Number(num).toString(16),2);
}
