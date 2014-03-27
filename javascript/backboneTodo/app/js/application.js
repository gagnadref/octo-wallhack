requirejs.config({
  baseUrl: '../lib/js',
  paths: {
    'App': '/js'
  }
});

requirejs(['App/views/AppView'], function(AppView){
  var appView = new AppView();
});