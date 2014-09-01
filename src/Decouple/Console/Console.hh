<?hh // strict
namespace Decouple\Console;
class Console {
  public function __construct(protected Vector<string> $arguments, protected Map<string,Command> $commands, private \Decouple\Decoupler\Decoupler $decoupler) {}
    /** Execute the App -- like main() **/
    public function execute() : void {
      /** TODO: Store script name separately from arguments; Pop filename, pop command, -- args -- **/

      /** Make sure we have more than just the filename **/
      if ($this->arguments->count() <= 1) {
        exit("You must supply a command!\n");
      }
      // Store the filename for the Input service
      $filename = $this->arguments->at(0);
      $command = $this->arguments->at(1);
      /** Make sure the command is registered **/
      if (!$this->commands->contains($command)) {
        /** TODO: Smart help text **/
        exit("Invalid command supplied\n");
      }
      $this->arguments->removeKey(1);
      $this->arguments->removeKey(0);
      /** Fetch the command class name **/
      $commandClass = (string)$this->commands->get($command);
      /** Use non-strict methods to reflect upon 'execute' method type hints **/
      $commandParams = getCommandParameters($commandClass);
      /** Fetch the type hinted classes as objects **/
      $passedParams = [];
      /** Register the console Input service singleton **/
      $this->decoupler->setSingleton('Decouple\Console\Service\Input', new Service\Input($this->arguments, $command, $filename));
      $this->decoupler->setSingleton('Decouple\Console\Service\Env', new Service\Env(getPaths()));
      /** Attempt to fetch the command paremeters as services from Decoupler, otherwise we don't have them **/
      /** TODO: Utilize Hack's custom type system with lambdas for contextual non-service parameters **/
      foreach($commandParams as $param) {
        if($this->decoupler->contains($param)) {
          $passedParams[] = $this->decoupler->service($param);
        } else {
          throw new \Exception(sprintf("Invalid service requested: %s; in %s", $param, $commandClass));
        }
      }
      /** Execute the command, providing requested classes **/
      executeCommand($commandClass, $passedParams);
    }
}
