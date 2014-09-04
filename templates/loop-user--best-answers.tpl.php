<?php
/**
 * @file loop-user-best-answers.tpl.php
 * Best answers block for user account
 *
 * Available variables:
 * - $answers_count
 * - $best_answers_count
 *
 */
?>
<div class="user-profile--best-answers">
<?php
print $answers_count;
print '--';
print $best_answers_count;
?>
</div>