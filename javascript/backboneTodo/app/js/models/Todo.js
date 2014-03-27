define(['backbone'], function(Backbone){ var Todo = Backbone.Model.extend({
  defaults: {
    title: "Click to change text !",
	completed: false
  }
});
  return Todo;
});