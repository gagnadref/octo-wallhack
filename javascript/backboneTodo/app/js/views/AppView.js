define(['backbone',
'App/views/TodoListView', 
'App/models/TodoList',
'App/models/Todo'], 
function(Backbone, TodoListView, TodoList, Todo) {
var AppView = Backbone.View.extend({
  template: _.template($("#appLayout").html()),
  tagName: 'div',
  initialize: function initializeApp(options) {
    this.options = options || {};
	this.render();
  },  
  render: function renderApp() {
    this.todoListView = new TodoListView({model: new TodoList()});  
	this.$el.html(this.template({}));
	$("#todoList", this.$el).html(this.todoListView.render().el);
	$("body").html(this.el);
	return this;
  },
  events: {
    'click #addTodo' : 'addNewTodo'
  },
  addNewTodo: function addTodo() {
    this.todoListView.model.add(new Todo());
  }
});
 return AppView;
});