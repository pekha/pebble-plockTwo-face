Pebble.addEventListener('appmessage',
  function(e) {
    console.log('Current settings message: ' + JSON.stringify(e));
    var url = "https://cdn.rawgit.com/pekha/pebble-plockTwo-face/1.2/config/"; // https://cdn.rawgit.com/pekha/pebble-plockTwo-face/1.0.1/configurable.html
    var dict = e.payload;
    var settings = {
      letter_off: dict.LETTER_OFF_KEY,
      letter_on: dict.LETTER_ON_KEY,
      background: dict.BACKGROUND_KEY
    };
    console.log('Current settings sent to config page: ' + JSON.stringify(JSON.stringify(settings)));
    Pebble.openURL(url + "#" + encodeURIComponent(JSON.stringify(settings)));
  }
);
Pebble.addEventListener("showConfiguration",
  function(e) {
    var dict = {
      'COMMAND_KEY' : 'GET_SETTINGS'
    };
    Pebble.sendAppMessage(dict);
  }
);
Pebble.addEventListener("webviewclosed",
  function(e) {
    var data = e.data || e.response;
    if (data !== ""){
      console.log('webviewclosed: ' + JSON.stringify(e));
      var configuration = JSON.parse(decodeURIComponent(data));
      var dict = {
        'BACKGROUND_KEY' : parseInt(configuration.background, 16),
        'LETTER_ON_KEY' : parseInt(configuration.letter_on, 16),
        'LETTER_OFF_KEY' : parseInt(configuration.letter_off, 16),
        'THINER_OFF_FONT_KEY' : configuration.thiner_off_font,
        'COMMAND_KEY' : 'SET_SETTINGS'
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