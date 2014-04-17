/**
 * DependencyInjector
 * * @param {Object} - object with dependencies
 */
var DependencyInjector = function (dependency) {
  this.dependency = dependency;
};

// Given a function, returns a new function with its dependencies resolved.
// Throws an Error if all dependencies were not resolved.
DependencyInjector.prototype.inject = function (func) {
  var splitKey = '####';

  // Retrieves the name of the arguments.
  var funcArguments = func.toString().replace(/\(/, splitKey)
    .replace(/\)/, splitKey)
    .split(splitKey)[1]
    .split(',');

  // Construct the injected dependencies array.
  var injectedArguments = [];
  for(var i = 0; i < funcArguments.length; i++) {
    var dep = this.dependency[funcArguments[i].replace(' ', '')];
    if(dep) {
      injectedArguments.push(dep);
    }
  }

  // Inject if all dependencies were resolved.
  if(injectedArguments.length === funcArguments.length) {
    return function() {
      return func.apply(this, injectedArguments);
    };
  }

  // Throw otherwise.
  throw new Error("All dependencies were not resolved.");
}

