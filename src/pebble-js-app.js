Pebble.addEventListener("showConfiguration",
  function(e) {
    Pebble.openURL("https://rawgit.com/pekha/pebble-plockTwo-face/nico/configurable.html");
  }
);
Pebble.addEventListener("webviewclosed",
  function(e) {
    console.log('Configuration window returned:  ' + e.data);
    if (e.data != "CANCELLED"){
      var configuration = e.data.split(';');
      var dict = {
        'BACKGROUND_KEY' : parseInt(configuration[0], 16), //BACKGROUND_KEY
        'LETTER_ON_KEY' : parseInt(configuration[2], 16), //LETTER_ON_KEY
        'LETTER_OFF_KEY' : parseInt(configuration[1], 16) // LETTER_OFF_KEY
      //  'THINER_OFF_FONT_KEY'
      };
      
      console.log('Dict: ' + JSON.stringify(dict));
      
      // Send a string to Pebble
      Pebble.sendAppMessage(dict,
        function(ee) {
          console.log('Send successful.' + ee);
        },
        function(ee) {
          console.log('Unable to deliver message with transactionId='+JSON.stringify(ee));
        }
      );      
    }
  }
);