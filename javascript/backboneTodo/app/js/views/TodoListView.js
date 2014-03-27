define(['backbone','App/views/TodoView'], function(Backbone, TodoView){
return Backbone.View.extend({
  tagName:'ul',
  initialize: function initalizeListView(){
	this.listenTo(this.model, "add", this.render);
  },
  render: function renderTodoList(){
	var element;
	this.$el.html("");
	for(var i = 0; i < this.model.length ; i++) {
	  var newTodoElement = new TodoView({model: this.model.models[i]});
	  this.$el.append(newTodoElement.render().$el);
	}  
	return this;
  }
});
});